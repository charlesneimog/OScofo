# import matplotlib.pyplot as plt
import numpy as np

ISPY4PD = False

try: 
    import pd
    array_size = 4096 
    SAMPLE_RATE = pd.get_sample_rate()
    print = pd.print
    ISPY4PD = True
except ImportError:
    SAMPLE_RATE = 44100
    print = print


def gaussian(x, amplitude, mu, sigma):
    # amp = amplitude * np.exp(-0.5 * ((x - center) / sigma) ** 2)
    return amplitude * np.exp(-((x - mu) ** 2) / (2 * sigma ** 2))


def main(Fund):
    arrLen = 4096
    array = np.zeros(arrLen)
    sigma = 0.2  # Standard deviation
    harmonics = 1
    # Build the Gaussian curve
    for h in range(harmonics):
        freq = (h + 1) * Fund
        mu = round(freq / (SAMPLE_RATE / arrLen))
        amplitude = (h + 1 ** 2)
        for i in range(arrLen):
            x = i
            gaussValue = np.exp(-0.5 * ((x - mu) / sigma) ** 2)
            array[i] += amplitude * gaussValue

    if ISPY4PD:
        pd.tabwrite("arr1", array, resize=True)
    else:
        import matplotlib.pyplot as plt
        plt.plot(array, marker='o', linestyle='None')  # Adiciona os pontos com bolinhas
        plt.plot(np.arange(arrLen), array.T)
        plt.title('Curvas Gaussianas')
        plt.xlabel('Ponto')
        plt.ylabel('Amplitude')
        # plt.ylim(0, 1)  # Define os limites do eixo y para garantir que a amplitude esteja entre 0 e 1
        plt.show()


def kl_setup():
    pd.add_object(main, "kl.array")


if __name__ == "__main__":
    main(440)

