import matplotlib.pyplot as plt


class Helpers:
    def __init__(self):
        pass

    def show_start_point(
        self,
        samples,
        start_point,
    ):
        """ """
        plt.figure(figsize=(10, 6))
        plt.plot(samples, label="Amostras de Áudio")
        plt.axvline(start_point, color="red", linestyle="--", label="Início da Análise")
        plt.xlabel("Índice da Amostra")
        plt.ylabel("Amplitude")
        plt.title("Amostras de Áudio e Início da Análise")

        # Add a legend
        plt.legend()

        # Show the plot
        plt.show()

    def show_spectrogram(self, magnitude):
        plt.figure(figsize=(10, 6))
        plt.plot(magnitude, label="Spectrograma")
        plt.xlabel(" Frequencia")
        plt.ylabel("Amplitude")
        plt.show()
