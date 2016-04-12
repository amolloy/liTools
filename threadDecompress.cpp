#include "pakDataTypes.h"
#include <thread>
#include <future>
#include <vector>

list<ThreadConvertHelper> g_lThreadedResources;
static std::atomic<uint32_t> g_iCurResource;
static std::atomic<uint32_t> g_iNumResources;
static std::mutex workMutex;
static std::mutex coutMutex;
bool g_bProgressOverwrite;
unsigned int g_iNumThreads;

//Create the folder that this resource ID's file will be placed in
void makeFolder(u32 resId)
{
	wstring sFilename = getName(resId);
	size_t pos = sFilename.find_last_of(L'/');
	if(pos != wstring::npos)
		sFilename = sFilename.substr(0,pos);
	sFilename = TEXT("./") + sFilename;
	//cout << "Creating folder " << ws2s(sFilename) << endl;
	ttvfs::CreateDirRec(ws2s(sFilename).c_str());
}

void decompressResource()
{
	while(true)
	{
		ThreadConvertHelper dh;
		wstring sFilename;
		
		{
			std::lock_guard<std::mutex> lock(workMutex);	
		
			if(!g_lThreadedResources.size())
			{
				break;
			}
			else
			{
				dh = g_lThreadedResources.front();
				sFilename = getName(dh.id);
				makeFolder(dh.id);
				g_lThreadedResources.pop_front();
			}
		}

		uint32_t currentResource = g_iCurResource.exchange(g_iCurResource + 1);
		if(!(sFilename == TEXT(RESIDMAP_NAME) && currentResource == 1))
		{
			if(g_bProgressOverwrite)
			{
				std::lock_guard<std::mutex> lock(coutMutex);
				cout << "\rDecompressing file " << currentResource << " out of " << g_iNumResources;
				cout.flush();
			}
			else
			{
				std::lock_guard<std::mutex> lock(coutMutex);
				cout << "Decompressing file " << currentResource << " out of " << g_iNumResources << ": " << ws2s(sFilename) << endl;
			}
		}
		
		if(sFilename == TEXT(RESIDMAP_NAME) && currentResource == 1)
		{
			g_iNumResources--;
		}

		if(dh.bCompressed)
		{
			uint8_t* tempData = decompress(&dh.data);
			if(tempData == NULL)
			{
				std::lock_guard<std::mutex> lock(coutMutex);
				cout << "Error decompressing file " << ws2s(sFilename) << endl;
				return;
			}
			free(dh.data.data);
			dh.data.data = tempData;
		}
		
		//See if this was a PNG image. Convert PNG images from the data in RAM
		if(sFilename.find(TEXT(".png")) != wstring::npos ||
		   sFilename.find(TEXT(".PNG")) != wstring::npos ||
		   sFilename.find(TEXT("coloritemicon")) != wstring::npos ||
		   sFilename.find(TEXT("colorbgicon")) != wstring::npos ||
		   sFilename.find(TEXT("greybgicon")) != wstring::npos)			//Also would include .png.normal files as well
		{
			convertToPNG(sFilename.c_str(), dh.data.data, dh.data.decompressedSize);	
		}
		else	
		{
			//For other file types, go ahead and write to the file before converting
			//Write this out to the file
			FILE* fOut = _wfopen(sFilename.c_str(), TEXT("wb"));
			if(fOut == NULL)
			{
				std::lock_guard<std::mutex> lock(coutMutex);
				cout << "Unable to open output file " << ws2s(sFilename) << endl;
				return;
			}
			fwrite(dh.data.data, 1, dh.data.decompressedSize, fOut);
			fclose(fOut);
		}
		free(dh.data.data);
		
		//Convert wordPackDict.dat to XML
		if(sFilename.find(TEXT("wordPackDict.dat")) != wstring::npos)
		{
			wordPackToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert sndmanifest.dat to XML
		else if(sFilename.find(TEXT("sndmanifest.dat")) != wstring::npos)
		{
			sndManifestToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert itemmanifest.dat to XML
		else if(sFilename.find(TEXT("itemmanifest.dat")) != wstring::npos)
		{
			itemManifestToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert letterdb.dat to XML
		else if(sFilename.find(TEXT("letterdb.dat")) != wstring::npos)
		{
			letterToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert catalogdb.dat to XML
		else if(sFilename.find(TEXT("catalogdb.dat")) != wstring::npos)
		{
			catalogToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert combodb.dat to XML
		else if(sFilename.find(TEXT("combodb.dat")) != wstring::npos)
		{
			comboDBToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert residmap.dat to XML
		else if(sFilename.find(TEXT("residmap.dat")) != wstring::npos)
		{
			residMapToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert .flac binary files to OGG
		else if(sFilename.find(TEXT(".flac")) != wstring::npos ||
				sFilename.find(TEXT(".FLAC")) != wstring::npos)
		{
			wstring s = sFilename;
			s += TEXT(".ogg");
#if 0
			binaryToOgg(sFilename.c_str(), s.c_str());
#else
			std::lock_guard<std::mutex> lock(coutMutex);
			cout << "Ignoring flac/ogg file" << std::endl;
#endif
			unlink(ws2s(sFilename).c_str());	//Delete temporary .flac file
		}
		
		//Convert vdata/fontmanifest.dat to XML
		else if(sFilename.find(TEXT("fontmanifest.dat")) != wstring::npos)
		{
			fontManifestToXML(sFilename);
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert font files to XML
		else if(sFilename.find(TEXT(".font.xml")) != wstring::npos)
		{
			fontToXML(sFilename);
		}
		
		//Convert vdata/loctexmanifest.bin to XML
		else if(sFilename.find(TEXT("loctexmanifest.bin")) != wstring::npos)
		{
			LoctexManifestToXML(sFilename);
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert vdata/myPicturesImage.dat to XML
		else if(sFilename.find(TEXT("myPicturesImage.dat")) != wstring::npos)
		{
			myPicturesToXML(sFilename);
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert vdata/smokeImage.dat to XML
		else if(sFilename.find(TEXT("smokeImage.dat")) != wstring::npos)
		{
			smokeImageToXML(sFilename);
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert vdata/fluidPalettes.dat to XML
		else if(sFilename.find(TEXT("fluidPalettes.dat")) != wstring::npos)
		{
			fluidPalettesToXML(sFilename);
			unlink(ws2s(sFilename).c_str());
		}
		
		if(sFilename == TEXT(RESIDMAP_NAME) && g_iCurResource == 1)
		{
			g_iCurResource--;
		}
	}
}

void threadedDecompress()
{
	g_iCurResource = 0;
	g_iNumResources = g_lThreadedResources.size();
		
	u32 numThreads = g_iNumThreads;
	if (numThreads == 0)
	{
		numThreads = std::thread::hardware_concurrency();
	}
	if(numThreads == 0)
	{
		numThreads = 2;
	}
	
	std::vector<std::future<void>> threads;
	
	for(u32 i = 0; i < numThreads; i++ )
    {
    	threads.emplace_back(std::async(decompressResource));
    }

	for (auto& f : threads)
	{
		f.wait();
	}
}







