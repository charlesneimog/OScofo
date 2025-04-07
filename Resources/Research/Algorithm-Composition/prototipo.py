from music21 import stream, note, scale, tempo
import random

# Create a stream
PATH = "/home/neimog/Nextcloud/MusicData/Samples/Orchidea/Keyboards"
composition = stream.Stream()

sharp_scale = scale.ChromaticScale("C#")
lista_de_ritmos = [
    [0.25, 0.5, 0.25],
    [0.5, 0.25, 0.25],
    [0.25, 0.25, 0.5],
    [0.5, 0.5],
    [1],
    [0.25, 0.25, 0.25, 0.25],
    [0.3333, 0.3333, 0.33333],
]

tempo_mark = tempo.MetronomeMark(number=60)
composition.append(tempo_mark)


total = 0
# Generate 16 notes
for _ in range(16):
    ritmo = random.choice(lista_de_ritmos)
    for i in range(0, len(ritmo)):
        value = ritmo[i]
        total += value
        p = random.choice(sharp_scale.getPitches("C4", "C5"))
        n = note.Note(p, quarterLength=value)
        if n.pitch.accidental:
            n.pitch.accidental.alter = n.pitch.accidental.alter
            n.pitch.accidental.displayType = "normal"
        n.pitch.spellingIsInferred = False
        composition.append(n)


bpm = 60
ms_per_quarter = 60000 / bpm
for n in composition.notes:
    onset_ms = n.offset * ms_per_quarter
    pitch_name = n.pitch.nameWithOctave
    if "-" in pitch_name:
        sharp_pitch = n.pitch.getEnharmonic()
        pitch_name = sharp_pitch.nameWithOctave
