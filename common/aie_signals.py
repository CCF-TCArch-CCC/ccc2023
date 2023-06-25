import numpy as np
import matplotlib.pyplot as plt

class SignalGenerator:

    def __init__(self, samples=2048, fs=44100):
        self.samples = samples
        self.fs = fs
        self.signal = self.generate_signal()

    def generate_cmpx(samples = 1024, fs = 100):
        f0, f1, f2, f3, f4 = 0.5, 2.5, 15.3, 16.7, 23.45
        ts = 1 / fs
        time = np.linspace(0, samples*ts, samples)

        tone_0 = 1 * np.cos(2*np.pi*f0*time)
        tone_1 = 0.2 * np.sin(2*np.pi*f1*time+0.1)
        tone_2 = 0.2 * np.sin(2*np.pi*f2*time)
        tone_3 = 0.1 * np.sin(2*np.pi*f3*time+0.1)
        tone_4 = 0.1 * np.sin(2*np.pi*f4*time+0.8)
        signal = (tone_0 + tone_1 + tone_2*1 + tone_3*1j + tone_4*1j)/2
        return signal,time
    
    def generate_real(samples = 1024, fs = 100):
        f0, f1, f2, f3, f4 = 0.5, 2.5, 15.3, 16.7, 23.45
        ts = 1 / fs
        time = np.linspace(0, samples*ts, samples)

        tone_0 = 1 * np.cos(2*np.pi*f0*time)
        tone_1 = 0.2 * np.sin(2*np.pi*f1*time+0.1)
        tone_2 = 0.2 * np.sin(2*np.pi*f2*time)
        tone_3 = 0.1 * np.sin(2*np.pi*f3*time+0.1)
        tone_4 = 0.1 * np.sin(2*np.pi*f4*time+0.8)
        signal = (tone_0 + tone_1 + tone_2*1 + tone_3*1 + tone_4*1)/2
        return signal,time 

class SignalPlotter:
    def __init__(self, data):
        self.data = data
    
    def plot_real_imaginary(self, num_samples=128):
        plt.figure(figsize=(10, 5))
        plt.plot(self.data.real[:num_samples], label='Real')
        plt.plot(self.data.imag[:num_samples], label='Imaginary')
        plt.xlabel('Sample')
        plt.ylabel('Amplitude')
        plt.title('Real and Imaginary Parts of the Signal')
        plt.legend()
        plt.grid(True)
        plt.show()