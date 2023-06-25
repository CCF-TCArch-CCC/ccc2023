import csv
import numpy as np
import matplotlib.pyplot as plt

class FileGen:
    def __init__(self, samples=1024):
        self.samples = samples


    def read_file(self, file: str, samples: int):
        value = np.zeros(samples, dtype=np.complex128)
        count = 0
        with open(file, 'r') as f:
            reader = csv.reader(f, delimiter=" ")
            for line in reader:
                if 'T' in line[0]:
                    continue
                for i in range(0, len(line), 2):
                    if line[i] != '':
                        value[count] = float(line[i]) + 1j * float(line[i + 1])
                        count = count + 1
        return value
    
    def write_refoutput(data: np.array, file: str, plio = 32, bits = 16, scale: bool=True):
        """
        data: samples
        file: output filename
        plio: bit width of the PLIO port
        bits: bit precision per sample
        """
        """Scale signal to use full precision"""
        maxr = np.max(np.abs(data.real))
        maxi = np.max(np.abs(data.imag))
        maxv = maxr if maxr > maxi else maxi
        vscale = 1
        data = data * (vscale if scale else 1)
        """Write value to file"""
        with open(file, 'w', newline='') as f:
            for i, v in enumerate(data):
                r = np.int16(v.real)
                c = np.int16(v.imag)
                f.write("{} {} ".format(r, c))
                # if (((i+1) % 4) == 0 and plio == 128) or (((i+1) % 2) == 1 and plio == 64):
                f.write('\n')
        
        return vscale

    def vector2file_cint16(data: np.array, file: str, plio = 32, bits = 16, scale: bool=True):
        """
        data: samples
        file: output filename
        plio: bit width of the PLIO port
        bits: bit precision per sample
        """
        """Scale signal to use full precision"""
        maxr = np.max(np.abs(data.real))
        maxi = np.max(np.abs(data.imag))
        maxv = maxr if maxr > maxi else maxi
        vscale = 2**int(np.floor(np.log2((1 << (bits-1)) / maxv)))
        data = data * (vscale if scale else 1)
        """Write value to file"""
        with open(file, 'w', newline='') as f:
            for i, v in enumerate(data):
                r = np.int16(v.real)
                c = np.int16(v.imag)
                f.write("{} {} ".format(r, c))
                # if (((i+1) % 4) == 0 and plio == 128) or (((i+1) % 2) == 1 and plio == 64):
                f.write('\n')
        
        return vscale


    def vector2file_int16(data: np.array, file: str, plio = 32, bits = 16, scale: bool=True):
        """
        data: samples
        file: output filename
        plio: bit width of the PLIO port
        bits: bit precision per sample
        """
        """Scale signal to use full precision"""
        maxr = np.max(np.abs(data.real))
        maxv = maxr
        vscale = 2**int(np.floor(np.log2((1 << (bits-1)) / maxv)))
        data = data * (vscale if scale else 1)
        """Write value to file"""
        with open(file, 'w', newline='') as f:
            for i, v in enumerate(data):
                r = np.int16(v.real)
                f.write("{} ".format(r))
                if (((i+1) % 8) == 0 and plio == 128) or (((i+1) % 2) == 1 and plio == 64):
                    f.write('\n')
        
        return vscale

