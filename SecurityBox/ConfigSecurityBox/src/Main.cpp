
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pcap/pcap.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/ether.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include "tinystr.h"
#include "tinyxml.h"

using namespace std;

int  child_pid = 0;

char fileConfigPath[1024];

char ipDataloger[20];
char macDataloger[20];
unsigned short portDataloger = 0;

char ipWIM[20];
char macWIM[20];

bool doneDataloger = false;

void write_config(const char* p_ipDataloger,const unsigned short p_portDataloger, const char* p_macDataloger, const char* p_macWIM)
{
	TiXmlDocument doc("config.xml");

	if(!doc.LoadFile())
	{
		doc.Clear();
		return;
	}

	TiXmlElement *eRoot = doc.RootElement(); // Bat2Chu
	TiXmlElement *eSetting = eRoot->FirstChildElement("Setting");

	TiXmlElement *eDataLoger = eSetting->FirstChildElement("datalogger");
	TiXmlElement *ePC = eSetting->FirstChildElement("pc");


	printf("+++++++++++++++Review again+++++++++++++++++\n");
	if(strlen(p_ipDataloger) > strlen("1.1.1.1"))
	{
		eDataLoger->SetAttribute("ip", p_ipDataloger);
		eDataLoger->SetAttribute("MAC", p_macDataloger);

		printf("IP Datalogger:   %s\n", p_ipDataloger);
		printf("MAC Datalogger:  %s\n", p_macDataloger);
	}

	if(p_portDataloger > 0)
	{
		eDataLoger->SetAttribute("port", p_portDataloger);
		printf("Port Datalogger: %d\n", p_portDataloger);
	}

	if(strlen(p_macWIM) > 0)
	{
		ePC->SetAttribute("MAC", p_macWIM);
		printf("MAC WIM:        %s\n", p_macWIM);
	}

	//printf("MACWIM: %s\n", p_macWIM);
	doc.SaveFile();

	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
	//doc.Clear();
	return;
}

void print_eth_addr(void *addr)
{
  printf("%s\n", ether_ntoa((struct ether_addr *)addr));
  kill(child_pid, 9);

  if(!doneDataloger)
  {
	  strcpy(macDataloger, ether_ntoa((struct ether_addr *)addr));
	  doneDataloger = true;
  }
  else
  {
	  strcpy(macWIM, ether_ntoa((struct ether_addr *)addr));
	  doneDataloger = false;
  }

}

void find_eth_addr(struct in_addr *search_ip, const struct pcap_pkthdr* pkthdr, const u_char *packet)
{
  struct ether_header *eth_hdr = (struct ether_header *)packet;

  if (ntohs(eth_hdr->ether_type) == ETHERTYPE_IP)
  {
    struct ip *ip_hdr = (struct ip *)(packet + sizeof(struct ether_header));
    if (ip_hdr->ip_dst.s_addr == search_ip->s_addr)
      print_eth_addr(eth_hdr->ether_dhost);
    if (ip_hdr->ip_src.s_addr == search_ip->s_addr)
      print_eth_addr(eth_hdr->ether_shost);
  }
}

int SearchMac(const char*ip)
{
	char *dev, errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* descr;
	bpf_u_int32 maskp, netp;

	if (!(dev = pcap_lookupdev(errbuf)))
	{
		fprintf(stderr, "%s\n", errbuf); return 1;
	}
	else
	{
		dev = "eth0";
		//printf("Vaooooooooooooooooooooooooooooooooo\n");
	}

	pcap_lookupnet(dev,&netp,&maskp,errbuf);

	if (!(descr = pcap_open_live(dev, BUFSIZ, 1, -1, errbuf)))
	{
		printf("pcap_open_live(): %s\n", errbuf); return 1;
	}

	struct in_addr search_ip;
	if (!inet_aton(ip, &search_ip))
	{
		fprintf(stderr, "bad ip\n");
		exit(1);
	}

	int pid = fork();

	if (pid == 0)
	{
		while (1)
		{
		  struct sockaddr_in sin;
		  sin.sin_family = PF_INET;
		  inet_aton(ip, &sin.sin_addr);
		  sin.sin_port = htons(1);
		  int s = socket(PF_INET, SOCK_STREAM, 0);
		  connect(s, (struct sockaddr *)&sin, sizeof(sin));
		  usleep(100000);
		};
	}
	else
	{
		child_pid = pid;
		pcap_loop(descr, 1 , (pcap_handler)find_eth_addr, (u_char *)&search_ip);
	}

	return 0;
}


int main()
{
	memset(ipDataloger,0 , sizeof(ipDataloger));
	memset(ipWIM,0 , sizeof(ipWIM));
	memset(macDataloger,0 , sizeof(macDataloger));
	memset(macWIM,0, sizeof(macWIM));
	portDataloger = 0;

	printf("IP Datalogger: "); //scanf("%[^\n]", ipDataloger);
	std::cin >> ipDataloger;

	//fflush(stdin);
	printf("Port:          "); scanf("%d", &portDataloger);

	//fflush(stdin);
	printf("IP WIM:        "); //scanf("%[^\n]", ipWIM);
	std::cin >> ipWIM;

	//fflush(stdin);
	printf("Save 2 file:   "); //scanf("%s", fileConfigPath);
	std::cin >> fileConfigPath;



	if(strcmp(ipDataloger, "0") == 0)
	{
		//printf("Vao 1\n");
		doneDataloger = true;
	}
	else
	{

		doneDataloger = false;
		SearchMac(ipDataloger);
	}


	if(strcmp(ipWIM, "0") != 0)
	{
		//printf("Vao 2\n");
		while(!doneDataloger)
		{
			this_thread::sleep_for(std::chrono::milliseconds(2));
		}
		SearchMac(ipWIM);
	}


	while(doneDataloger)
	{
		this_thread::sleep_for(std::chrono::milliseconds(2));
	}

	write_config(ipDataloger, portDataloger, macDataloger, macWIM);

}
