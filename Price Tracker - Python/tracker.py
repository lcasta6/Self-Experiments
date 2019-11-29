import requests

from bs4 import BeautifulSoup

URL = 'https://www.amazon.com/LG-27UK850-W-Monitor-Connectivity-FreeSync/dp/B078GVTD9N/ref=sr_1_5?keywords=4k&pf_rd_i=11598814011&pf_rd_m=ATVPDKIKX0DER&pf_rd_p=641aa8da-8ae5-441e-a9c4-f32f22ba08bf&pf_rd_r=DPKWSZ773P0157R5VXJB&pf_rd_s=merchandised-search-3&pf_rd_t=101&qid=1575006731&s=pc&sr=1-5'

head = {"User-Agent": 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:70.0) Gecko/20100101 Firefox/70.0'}

page = requests.get(URL, headers=head)

soup = BeautifulSoup(page.content, 'html.parser')
soup2 = BeautifulSoup(soup.prettify(), 'html.parser')

title = soup2.find(id="priceblock_ourprice").get_text()

print(title)
