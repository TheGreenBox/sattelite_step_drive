import matplotlib
matplotlib.use('pdf')

import matplotlib.pyplot as plotter
from matplotlib.backends.backend_pdf import PdfPages

allLogFiles = ('adc_0.dat', 'adc_1.dat', 'adc_2.dat', 'adc_3.dat', 'adc_4.dat')

def formHistogramDataFor(filename):
    logLines = open(filename).readlines()

    histogram = {}
    for adc_reading in logLines:
        adc_reading = int(adc_reading)
        if adc_reading in histogram:
            histogram[adc_reading] += 1
        else:
            histogram[adc_reading] = 1

    for key in range(min(histogram), max(histogram)):
        if key not in histogram:
            histogram[key] = 0

    histKeys = list(histogram.keys())
    histKeys.sort()

    histHeights = []
    for key in histKeys:
        histHeights.append(histogram[key])

    return histKeys, histHeights

def plotHistogramOf(filename):
    histKeys, histHeights = formHistogramDataFor(filename)

    plotter.bar(range(min(histKeys), max(histKeys) + 1), histHeights)
    plotter.xlabel('ADC value')
    plotter.ylabel('Number of hits (out of ' + str(sum(histHeights)) + ')')
    plotter.title(filename.upper())

def plotAllLogsToPdf(resFileName):
    pp = PdfPages(resFileName + '.pdf')
    for filename in allLogFiles:
        plotHistogramOf(filename)
        pp.savefig()
        plotter.cla()

    pp.close()

# read 'Using Histogram Techniques to Measure A/D Converter Noise'
# at analog.com for math explanation

temp_sigma = 1
def integrand(z):
    exponent = ((-z) ** 2) / (2 * (temp_sigma ** 2))
    return math.exp(exponent)

def calculateX0(P):
    lastIntegral = 0
    for upperLimit in numpy.arrange(-5.0, 0, 0.001):
        integral = 2 / (temp_sigma * math.sqrt(2 * math.pi)) * quad(integrand, -numpy.inf, upperLimit)
        if lastIntegral < P < integral:
            return upperLimit

        lastIntegral = integral

    print('unable to find upper integration limit that matches given P')

def calculateRmsNoiseFrom(filename):
    from scipy.integrate import quad
    import numpy

    histKeys, histHeights = formHistogramDataFor(filename)
    mainBinMissProbability = 1 - max(histHeights) / sum(histHeights)
    x0 = calculateX0(mainBinMissProbability)
    print('x0 = ' + x0)
    print('adc nose is ' + str(x0 / (-0.5)) + ' LSB')
