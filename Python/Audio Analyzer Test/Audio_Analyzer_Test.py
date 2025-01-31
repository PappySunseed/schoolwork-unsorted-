import librosa
import numpy as np
import pygame

filename =  librosa.ex('brahms')

class AudioAnalyzer:
    def __init__(self):

        self.frequencies_index_ratio = 0  # array for frequencies
        self.time_index_ratio = 0  # array of time periods
        self.spectrogram = None  # a matrix that contains decibel values according to frequency and time indexes
    def load(self, filename):

        time_series, sample_rate = librosa.load(filename)  # getting information from the file

        # getting a matrix which contains amplitude values according to frequency and time indexes
        stft = np.abs(librosa.stft(time_series, hop_length=512, n_fft=2048*4))

        self.spectrogram = librosa.amplitude_to_db(stft, ref=np.max)  # converting the matrix to decibel matrix

        frequencies = librosa.core.fft_frequencies(n_fft=2048*4)  # getting an array of frequencies

        # getting an array of time periodic
        times = librosa.core.frames_to_time(np.arange(self.spectrogram.shape[1]), sr=sample_rate, hop_length=512, n_fft=2048*4)

        self.time_index_ratio = len(times)/times[len(times) - 1]

        self.frequencies_index_ratio = len(frequencies)/frequencies[len(frequencies)-1]
    

    def get_decibel(self, target_time, freq):

        return self.spectrogram[int(freq*self.frequencies_index_ratio)][int(target_time*self.time_index_ratio)]

        # returning the current decibel according to the indexes which found by binary search
        # return self.spectrogram[bin_search(self.frequencies, freq), bin_search(self.times, target_time)]

    def get_decibel_array(self, target_time, freq_arr):

        arr = []

        for f in freq_arr:
            arr.append(self.get_decibel(target_time,f))

        return arr

def clamp(min_value, max_value, value):

    if value < min_value:
        return min_value

    if value > max_value:
        return max_value

    return value


class AudioBar:

    def __init__(self, x, y, freq, color, width=50, min_height=10, max_height=100, min_decibel=-80, max_decibel=0):

        self.x, self.y, self.freq = x, y, freq

        self.color = color

        self.width, self.min_height, self.max_height = width, min_height, max_height

        self.height = min_height

        self.min_decibel, self.max_decibel = min_decibel, max_decibel

        self.__decibel_height_ratio = (self.max_height - self.min_height)/(self.max_decibel - self.min_decibel)

    def update(self, dt, decibel):

        desired_height = decibel * self.__decibel_height_ratio + self.max_height

        speed = (desired_height - self.height)/0.1

        self.height += speed * dt

        self.height = clamp(self.min_height, self.max_height, self.height)

    def render(self, screen):

        pygame.draw.rect(screen, self.color, (self.x, self.y + self.max_height - self.height, self.width, self.height))





analyzer = AudioAnalyzer()
analyzer.load(filename)
pygame.init()
screen = pygame.display.set_mode((800, 600))
pygame.mixer.music.load(filename)
pygame.mixer.music.play(0)

bars = []
x = 0
frequencies = np.arange(100, 8000, 100)
for c in frequencies:
    bars.append(AudioBar(x, 300, c, (255, 0, 0), max_height=400, width=50))
    x += 50

running = True
clock = pygame.time.Clock()
while running:
    dt = clock.tick(60) / 1000.0
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    screen.fill((255, 255, 255))
    for b in bars:
        b.update(dt, AudioAnalyzer.get_decibel(b, pygame.mixer.music.get_pos() / 1000.0, b.freq))
        b.render(screen)
    pygame.display.flip()

pygame.quit()
