'''
Pulling Yahoo CSV Data
'''

import urllib2
import urllib
import datetime
import os
import time
import csv
import QSTK.qstkutil.qsdateutil as du

def get_yahoo_data(data_path, ls_symbols):
    '''Read data from Yahoo
    @data_path : string for where to place the output files
    @ls_symbols: list of symbols to read from yahoo
    '''
    # Create path if it doesn't exist
    if not (os.access(data_path, os.F_OK)):
        os.makedirs(data_path)

    ls_missed_syms = []
    # utils.clean_paths(data_path)

    _now = datetime.datetime.now()
    # Counts how many symbols we could not get
    miss_ctr = 0
    for symbol in ls_symbols:
        # Preserve original symbol since it might
        # get manipulated if it starts with a "$"
        symbol_name = symbol
        if symbol[0] == '$':
            symbol = '^' + symbol[1:]

	symbol_data = list()
        print "Getting {0}".format(symbol)

        try:
	    # start_month: a = 0-11. start_date: b = 1-31. start_year: c
            params = urllib.urlencode ({'a':(_now.month-8+12)%12, 'b':_now.day, 'c':2014, 'd':_now.month-1, 'e':_now.day, 'f':_now.year, 's': symbol})
            url = "http://ichart.finance.yahoo.com/table.csv?%s" % params
            url_get = urllib2.urlopen(url)

#            header = url_get.readline()
            header = ('SYM,' + url_get.readline())

            symbol_data.append (symbol + ',' + url_get.readline())
#            symbol_data.append(url_get.readline())
            while (len(symbol_data[-1]) > len(symbol)+1):
                symbol_data.append(symbol + ',' + url_get.readline())
#                symbol_data.append(url_get.readline())

            # The last element is going to be the string of length zero.
            # We don't want to write that to file.
            symbol_data.pop(-1)
            #now writing data to file
            f = open (data_path + symbol_name + ".csv", 'w')

            #Writing the header
            f.write (header)

            while (len(symbol_data) > 0):
                f.write (symbol_data.pop(0))

            f.close()

        except urllib2.HTTPError:
            miss_ctr += 1
            ls_missed_syms.append(symbol_name)
            print "Unable to fetch data for stock: {0} at {1}".format(symbol_name, url)
        except urllib2.URLError:
            miss_ctr += 1
            ls_missed_syms.append(symbol_name)
            print "URL Error for stock: {0} at {1}".format(symbol_name, url)

    print "All done. Got {0} stocks. Could not get {1}".format(len(ls_symbols) - miss_ctr, miss_ctr)
    return ls_missed_syms

########

def read_symbols(s_symbols_file):
    '''Read a list of symbols'''
    ls_symbols = []
    ffile = open(s_symbols_file, 'r')
    for line in ffile.readlines():
        str_line = str(line)
        if str_line.strip():
            ls_symbols.append(str_line.strip())
    ffile.close()
    return ls_symbols

########
	
def write_dates_data(data_path, filename):
    if not (os.access(data_path, os.F_OK)):
        os.makedirs(data_path)
    writer = csv.writer(open(filename, 'wb'), delimiter=',')

    _now = datetime.datetime.now()
    dt_start = datetime.datetime(2014, (_now.month-7+12)%12, _now.day)
    dt_last = datetime.datetime(_now.year, _now.month, _now.day)
    dt_end= dt_last + datetime.timedelta(days=1)
    ldt_timestamps = du.getNYSEdays(dt_start, dt_end, datetime.timedelta(hours=16))

    ls_dates = []	
    for i in (range(0, len(ldt_timestamps))):
      entry_year = ldt_timestamps[i].year
      entry_month = ldt_timestamps[i].month
      entry_day = ldt_timestamps[i].day
      market_date = "{0}-{1:02d}-{2:02d}".format(entry_year,entry_month,entry_day)
      writer.writerow([market_date])

########

def main():
    '''Main Function'''
    path = './'+time.strftime("%Y%m%d")+'/'
	
    ls_symbols = read_symbols('symbols.txt')
#    ls_symbols = read_symbols('SP500_2014.txt')
    
    get_yahoo_data(path, ls_symbols)

    datesfile = path+'/_dates.csv'
    write_dates_data(path, datesfile)

########

if __name__ == '__main__':
    main()

