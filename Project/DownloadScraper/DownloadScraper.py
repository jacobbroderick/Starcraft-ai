#webcrawler
import requests 
from BeautifulSoup import BeautifulSoup
import urllib2
import mysql.connector

#Connect to MySql
connection = mysql.connector.connect(host='oniddb.cws.oregonstate.edu', 
						password='sMIlEhpLXriUXHbo')

#Get all replay ID's from gosugamers.net
def getReplayLinks():
	url = 'http://www.gosugamers.net/starcraft/replays-archive'
	response = requests.get(url)
	html = response.content

	soup = BeautifulSoup(html)
	replayLinkTable = []
	#Get all the table rows that have the link stored in the data-href value.
	replayLinkTable = soup.findAll('tr', {"data-href" : lambda L: L and L.startswith('replays/')})

	return replayLinkTable;

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

#main code	
replayLinks = []
replayLinks = getReplayLinks();

#test line
downloadReplay(replayLinks[0]['data-href'])
