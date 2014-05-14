import matplotlib.pyplot as plotter
from matplotlib.backends.backend_pdf import PdfPages

allLogFiles = ('adc_0.dat', 'adc_1.dat', 'adc_2.dat', 'adc_3.dat', 'adc_4.dat')


def extractData(filename):
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
    histKeys, histHeights = extractData(filename)

    plotter.bar(range(min(histKeys), max(histKeys) + 1), histHeights)
    plotter.xlabel('ADC value')
    plotter.ylabel('Number of hits (out of ' + str(sum(histHeights)) + ')')
    plotter.title(filename.upper())


def plotAllTo(resFileName):
    pp = PdfPages(resFileName + '.pdf')
    for filename in allLogFiles:
        plotHistogramOf(filename)
        pp.savefig()
        plotter.cla()

    pp.close()
