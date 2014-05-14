import math
from scipy.integrate import quad
import numpy

import histogram_creator as hist

fake_sigma = 1


def integrand(z):
    exponent = -(z ** 2) / (2 * (fake_sigma ** 2))
    return math.exp(exponent)


def calculateX0(P):
    lastIntegral = 0
    for upperLimit in numpy.linspace(-5.0, 0, 5 / 0.001):
        integral = (2 / (fake_sigma * math.sqrt(2 * math.pi))) \
            * quad(integrand, -numpy.inf, upperLimit)[0]

        if lastIntegral <= P < integral:
            return upperLimit

        lastIntegral = integral

    print('unable to find upper integration limit that matches given P')


# read 'Using Histogram Techniques to Measure A/D Converter Noise'
# at analog.com for math explanation
def calculateRmsNoiseFrom(filename):
    histKeys, histHeights = hist.extractData(filename)
    mainBinMissProbability = 1 - max(histHeights) / sum(histHeights)
    x0 = calculateX0(mainBinMissProbability)
    sigma = 0.5 / (-x0)
    return sigma


def calculateExpectedValueFrom(filename):
    histKeys, histHeights = hist.extractData(filename)
    allMeasures = sum(histHeights)
    index = 0
    expectedValue = 0
    for adcVal in histKeys:
        expectedValue += adcVal * histHeights[index] / allMeasures
        index += 1

    return expectedValue, max(histKeys)

ALL_ADC_BITS = 12


def calculateNoiseFreeBitsByExpectedValueFrom(filename):
    expectedValue, maxValue = calculateExpectedValueFrom(filename)
    return math.log(2 ** ALL_ADC_BITS / (maxValue - expectedValue))


def calculateNoiseFreeBitsFrom(filename):
    rmsNoise = calculateRmsNoiseFrom(filename)
    peakToPeakNoise = 6.6 * rmsNoise
    noiseFreeBits = math.floor(math.log((2**ALL_ADC_BITS)
                                        / peakToPeakNoise, 2))

    print('adc has ' + str(noiseFreeBits)
          + ' noise-free bits according to integral estimation')

    expectedValue, maxValue = calculateExpectedValueFrom(filename)
    noiseFreeBits = math.floor(math.log(2 ** ALL_ADC_BITS
                                        / (maxValue - expectedValue), 2))

    print('adc has ' + str(noiseFreeBits)
          + ' noise-free bits according to expected value calculation')
