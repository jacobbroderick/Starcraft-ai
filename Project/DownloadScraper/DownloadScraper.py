#webcrawler
import requests 
from BeautifulSoup import BeautifulSoup
import urllib2
import sys
#Syntax for compiling program:
#
#DownloadScraper .py <StarcraftRace>
#

#Get all replay ID's from gosugamers.net
def downloadReplays(race):
	url = 'http://www.gosugamers.net/starcraft/replays-archive'
	response = requests.get(url)
	pageHtml = response.content
	for i in range(2, 257):
		soup = BeautifulSoup(pageHtml)
		replayLinkTable = []
		#Get all the table rows that have the link stored in the data-href value.
		replayLinkTable = soup.findAll('tr', {"data-href" : lambda L: L and L.startswith('replays/')})
		for row in replayLinkTable:
			visitDownloadPage(row['data-href'])
			
		url = 'http://www.gosugamers.net/starcraft/replays-archive?page='
		url += str(i)
		response = requests.get(url)
		pageHtml = response.content
		
	return;

#Visit the page to check replay details.
def visitDownloadPage(replayString):
	url = 'http://www.gosugamers.net/starcraft/'
	url += replayString
	response = requests.get(url)
	pageHtml = response.content
	
	soup = BeautifulSoup(pageHtml)
	replayRaces = []
	#Get all src tags with title Terran
	replayRaces = soup.findAll('img', title='Terran')
	if replayRaces:
		downloadReplay(replayString);
	
	return;
	
#Downloads the replay using the replay ID.
def downloadReplay(replayID):
	replayID = replayID.replace("replays/", "")
	url = 'http://www.gosugamers.net/starcraft/replays/download-old?id='
	url += str(replayID)
	rq = urllib2.Request(url)
	response = urllib2.urlopen(rq)
	replay = open("replays/" + replayID, "w+")
	replay.write(response.read())
	replay.close()
	
	return;

def main():
	if len(sys.argv) != 2:
		print 'Usage. Please use the following syntax: DownloadScraper.py <StarcraftRace>'
		return;
	else:
	
		print 'Downloading replays... This may take some time...'
		downloadReplays(sys.argv[1]);	
	
if __name__ == "__main__": main()
	
	
	
	
	
	
	
	
	
	
	