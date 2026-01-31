import sounddevice as sd
import soundfile as sf
import ffmpeg
import pydub as py
import numpy as np

#py.AudioSegment.ffmpeg = r"c:\users\魏一诺\appdata\local\programs\python\python312\lib\site-packages\ffmpeg"

filename = 'music.wav'
data, fs = sf.read(filename, dtype="float32")

sd.play(data, fs)
status = sd.wait()

duration = len(data) / fs

for t in range(1, int(duration), 2):
    start = int(t * fs)
    end = int((t + 1) * fs)
    data = np.concatenate((data[:start], data[end:]))

sf.write('processed_music.wav', data, fs)
