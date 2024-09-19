import os

import librosa
import csv

from OScofo import OScofo

root = os.path.dirname(os.path.abspath(__file__))

BLOCKS_TO_COMPUTE = 500

for e in range(0, 2):
    print("")
    AUDIO_FILE = root + f"/Test{e}.wav"
    SCORE_FILE = root + f"/Test{e}.txt"

    print("# ──────────────────────────────────────")
    print("Testing Audio file:", AUDIO_FILE)
    print("# ──────────────────────────────────────")

    HOP_SIZE = 512
    FFT_SIZE = 4096
    SR = 48000

    # Initialize OScofo
    OpenScofo = OScofo(SR, FFT_SIZE, HOP_SIZE)
    OpenScofo.ParseScore(SCORE_FILE)
    # OpenScofo.SetdBTreshold(-45)

    samples, sr = librosa.load(AUDIO_FILE, sr=SR)

    event = 0
    onset = 0
    block = 0
    Events = {}

    for i in range(0, len(samples), HOP_SIZE):
        audioBlock = samples[i : i + FFT_SIZE]

        if len(audioBlock) != FFT_SIZE:
            print("End of audio")
            break
        if OpenScofo.ProcessBlock(audioBlock):
            currentEvent = OpenScofo.GetEventIndex()
            currentBpm = OpenScofo.GetLiveBPM()

            onset += 1 / (SR / HOP_SIZE)
            if currentEvent != event:
                event = currentEvent
                onset_ms = int(onset * 1000)
                base = 500
                resultado = 0
                for i in range(1, event + 1):
                    resultado = base * (i - 1)

                if abs(resultado - onset_ms) < 50:
                    print(
                        f"\033[92mEvent: {event:02d}",
                        "in",
                        f"{onset_ms:04d} ms |",
                        f"BPM: {currentBpm:.2f}\033[0m",
                    )

                else:
                    print(
                        f"\033[91mEvent: {event:02d}",
                        "in",
                        f"{onset_ms:04d} ms |",
                        f"BPM: {currentBpm:.2f}\033[0m",
                    )

                Events[event] = {
                    "onset": onset_ms,
                    "bpm": currentBpm,
                    "event": f"Event {event}",
                }

        else:
            raise Exception("Error in processing block")
        block += 1
        # if block > BLOCKS_TO_COMPUTE:
        #     break
        # input("Press Enter to continue...")

    csv_file = root + f"/Test{e}.csv"
    with open(csv_file, mode="w", newline="") as file:
        writer = csv.writer(file)
        for key, value in Events.items():
            writer.writerow([value["onset"] / 1000, value["event"]])

    print(f'CSV file "{csv_file}" has been created.')
