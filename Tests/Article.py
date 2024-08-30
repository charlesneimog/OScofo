from OScofo import OScofo
import soundfile as sf

sr = 48000
windowSize = 4096
blockSize = 1024
data, fs = sf.read("/Test1.wav")

OScofo = OScofo(sr, windowSize, blockSize)
OScofo.ParseScore("./Test1.txt")

# Process Audio
event = -1
onset = 0
for i in range(0, len(data), blockSize):
    audioBlock = data[i : i + windowSize]
    if len(audioBlock) != windowSize:
        break

    if OScofo.ProcessBlock(audioBlock):
        currentEvent = OScofo.GetEventIndex()
        if currentEvent != event:
            event = currentEvent
            print("Event: ", event, " at ", onset)
        onset += 1 / (sr / blockSize)
    else:
        raise Exception("Error in processing block")
print("Processing done")
