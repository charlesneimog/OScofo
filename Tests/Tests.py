import os
import warnings
import librosa
import csv
import unittest


from OScofo import OScofo

MAX_ERROR_TOL = 250


os.chdir(os.path.dirname(os.path.abspath(__file__)))


class OScofoTest(unittest.TestCase):
    def setUp(self):
        self.warning_context = warnings.catch_warnings(record=True)
        self.warning_context.__enter__()
        warnings.simplefilter("ignore", category=DeprecationWarning)

    def open_expected_csv(self, root):
        csv_file = f"{root}/expected.csv"
        with open(csv_file, mode="r") as file:
            reader = csv.reader(file)
            reader_list = list(reader)

        self.expected_dict = {}
        for row in list(reader_list):
            self.expected_dict[int(row[1])] = float(row[0])

    def save_csv(self, root):
        csv_file = f"{root}/result.csv"
        with open(csv_file, mode="w", newline="") as file:
            writer = csv.writer(file)
            for key, value in self.events_dict.items():
                writer.writerow(
                    [
                        value["onset"] / 1000,
                        value["event"],
                        value["diff"],
                        value["good"],
                    ]
                )

        exp = len(self.expected_dict)
        det = len(self.events_dict)
        print(f"Events Expected {exp} | Events Detected {det}")

    def report(self, event, onset, bpm):
        onset_ms = int(onset * 1000)
        try:
            event_exp_onset = self.expected_dict[event + 1] * 1000
        except:
            return
        event += 1
        if abs(event_exp_onset - onset_ms) < MAX_ERROR_TOL:
            print(
                f"\033[92mEvent: {event:02d}",
                "in",
                f"{onset_ms:04d} ms |",
                f"BPM: {bpm:.2f}\033[0m",
            )
        else:
            print(
                f"\033[91mEvent: {event:02d}",
                "in",
                f"{onset_ms:04d} ms |",
                f"BPM: {bpm:.2f}\033[0m",
            )
        self.events_dict[event] = {
            "onset": onset_ms,
            "bpm": bpm,
            "event": f"{event}",
            "diff": abs(event_exp_onset - onset_ms),
            "good": abs(event_exp_onset - onset_ms) < MAX_ERROR_TOL,
        }

    def ordinary_test(self, test_root, sr, fft_size, hop_size):
        piece_name = test_root.replace("./", "")
        print(f"\n\033[94mTesting {piece_name}\033[0m")
        self.open_expected_csv(test_root)
        wav_file = f"{test_root}/audio.wav"
        score_file = f"{test_root}/score.txt"
        OpenScofo = OScofo(sr, fft_size, hop_size)
        OpenScofo.ParseScore(score_file)
        samples, sr = librosa.load(wav_file, sr=sr)
        print(samples)

        event = 0
        onset = 0
        block = 0
        self.events_dict = {}

        for i in range(0, len(samples), hop_size):
            audioBlock = samples[i : i + fft_size]

            if len(audioBlock) != fft_size:
                audioBlock = librosa.util.fix_length(audioBlock, size=fft_size)

            if OpenScofo.ProcessBlock(audioBlock):
                currentEvent = OpenScofo.GetEventIndex()
                currentBpm = OpenScofo.GetLiveBPM()
                onset += 1 / (sr / hop_size)
                if currentEvent != event:
                    self.report(event, onset, currentBpm)
                event = currentEvent
            else:
                raise Exception("Error in processing block")
            block += 1
        self.save_csv(test_root)
        print()

    def test_1scaleC4(self):
        self.ordinary_test("./Scale-C4", 48000, 4096, 1024)

    def test_1scaleC5(self):
        self.ordinary_test("./Scale-C5", 48000, 4096, 1024)

    def test_2synrix(self):
        self.ordinary_test("./Syrinx", 48000, 4096, 1024)

    def test_3bwv1013(self):
        self.ordinary_test("./BWV-1013", 48000, 4096, 1024)


if __name__ == "__main__":
    unittest.main(failfast=True)
