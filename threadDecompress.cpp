#include <mutex>
#include <thread>
#include "pakDataTypes.h"
#include "residmap.h"
#include "stringTools.h"
#include "zpipe.h"
#include "image.h"

list<ThreadConvertHelper> g_lThreadedResources;
u32 g_iCurResource;
u32 g_iNumResources;
std::mutex g_Mutex;
bool g_bProgressOverwrite;
unsigned int g_iNumThreads;

//Create the folder that this resource ID's file will be placed in
void makeFolder(u32 resId)
{
	wstring sFilename = getName(resId);
	size_t pos = sFilename.find_last_of(L'/');
	if(pos != wstring::npos)
		sFilename = sFilename.substr(0,pos);
	sFilename = L"./" + sFilename;
	//cout << "Creating folder " << ws2s(sFilename) << endl;
	ttvfs::CreateDirRec(ws2s(sFilename).c_str());
}

void decompressResource()
{
	for(bool bDone = false;!bDone;)	//Loop until we're done
	{
		ThreadConvertHelper dh;
		wstring sFilename;
		std::lock_guard<std::mutex> lock(g_Mutex);

		if(!g_lThreadedResources.size())	//Done
		{
			bDone = true;
		}
		else
		{
			//Grab the top item off the list
			dh = g_lThreadedResources.front();
			sFilename = getName(dh.id);	//Mutex on this too, since getName() isn't really threadsafe
			makeFolder(dh.id);	//Also create folder (not threadsafe, either)
			g_lThreadedResources.pop_front();	//Done with this element
		}
		
		//Let user know which resource we're converting now
		if(!bDone)
		{
			g_iCurResource++;
			if(!(sFilename == RESIDMAP_NAME && g_iCurResource == 1))
			{
				if(g_bProgressOverwrite)
				{
					cout << "\rDecompressing file " << g_iCurResource << " out of " << g_iNumResources;
					cout.flush();
				}
				else
					cout << "Decompressing file " << g_iCurResource << " out of " << g_iNumResources << ": " << ws2s(sFilename) << endl;
			}
		}
		
		// Release ownership of the mutex object
		if(sFilename == RESIDMAP_NAME && g_iCurResource == 1)	//Don't release residmap.dat mutex until we've read in all the filenames
		{
			g_iNumResources--;
		}

		if(bDone)
		{
			continue;	//Stop here if done
		}
			
		if(dh.bCompressed)	//Compressed
		{
			uint8_t* tempData = decompress(&dh.data);
			if(tempData == NULL)
			{
				cout << "Error decompressing file " << ws2s(sFilename) << endl;
				return;
			}
			free(dh.data.data);	//Free this compressed memory
			dh.data.data = tempData;	//Now we have the decompressed data
		}
		
		//See if this was a PNG image. Convert PNG images from the data in RAM
		if(sFilename.find(L".png") != wstring::npos ||
		   sFilename.find(L".PNG") != wstring::npos ||
		   sFilename.find(L"coloritemicon") != wstring::npos ||
		   sFilename.find(L"colorbgicon") != wstring::npos ||
		   sFilename.find(L"greybgicon") != wstring::npos)			//Also would include .png.normal files as well
		{
			convertToPNG(sFilename.c_str(), dh.data.data, dh.data.decompressedSize);	//Do the conversion to PNG
		}
		else	//For other file types, go ahead and write to the file before converting
		{
			//Write this out to the file
			FILE* fOut = fopen(ws2s(sFilename).c_str(), "wb");
			if(fOut == NULL)
			{
				cout << "Unable to open output file " << ws2s(sFilename) << endl;
				return;
			}
			fwrite(dh.data.data, 1, dh.data.decompressedSize, fOut);
			fclose(fOut);
		}
		free(dh.data.data);	//Free memory from this file
		
		/*
		//Convert wordPackDict.dat to XML
		if(sFilename.find(L"wordPackDict.dat") != wstring::npos)
		{
			wordPackToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert sndmanifest.dat to XML
		else if(sFilename.find(L"sndmanifest.dat") != wstring::npos)
		{
			sndManifestToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert itemmanifest.dat to XML
		else if(sFilename.find(L"itemmanifest.dat") != wstring::npos)
		{
			itemManifestToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert letterdb.dat to XML
		else if(sFilename.find(L"letterdb.dat") != wstring::npos)
		{
			letterToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert catalogdb.dat to XML
		else if(sFilename.find(L"catalogdb.dat") != wstring::npos)
		{
			catalogToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert combodb.dat to XML
		else if(sFilename.find(L"combodb.dat") != wstring::npos)
		{
			comboDBToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert residmap.dat to XML
		else if(sFilename.find(L"residmap.dat") != wstring::npos)
		{
			residMapToXML(sFilename.c_str());
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert .flac binary files to OGG
		else if(sFilename.find(L".flac") != wstring::npos ||
				sFilename.find(L".FLAC") != wstring::npos)
		{
			wstring s = sFilename;
			s += L".ogg";
			binaryToOgg(sFilename.c_str(), s.c_str());
			unlink(ws2s(sFilename).c_str());	//Delete temporary .flac file
		}
		
		//Convert vdata/fontmanifest.dat to XML
		else if(sFilename.find(L"fontmanifest.dat") != wstring::npos)
		{
			fontManifestToXML(sFilename);
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert font files to XML
		else if(sFilename.find(L".font.xml") != wstring::npos)
		{
			fontToXML(sFilename);
		}
		
		//Convert vdata/loctexmanifest.bin to XML
		else if(sFilename.find(L"loctexmanifest.bin") != wstring::npos)
		{
			LoctexManifestToXML(sFilename);
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert vdata/myPicturesImage.dat to XML
		else if(sFilename.find(L"myPicturesImage.dat") != wstring::npos)
		{
			myPicturesToXML(sFilename);
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert vdata/smokeImage.dat to XML
		else if(sFilename.find(L"smokeImage.dat") != wstring::npos)
		{
			smokeImageToXML(sFilename);
			unlink(ws2s(sFilename).c_str());
		}
		
		//Convert vdata/fluidPalettes.dat to XML
		else if(sFilename.find(L"fluidPalettes.dat") != wstring::npos)
		{
			fluidPalettesToXML(sFilename);
			unlink(ws2s(sFilename).c_str());
		}
		*/
		
		if(sFilename == RESIDMAP_NAME && g_iCurResource == 1)
		{
			g_iCurResource--;
		}
	}
	return;
}

void threadedDecompress()
{
	g_iCurResource = 0;
	g_iNumResources = g_lThreadedResources.size();
	
	auto iNumThreads = std::thread::hardware_concurrency();
	if(g_iNumThreads != 0)
	{
		iNumThreads = g_iNumThreads;
	}

	std::vector<std::thread> aThread;
	
	//Start threads
	for(u32 i = 0; i < iNumThreads; i++ )
    {
    	aThread.emplace_back(decompressResource);
    }

	for(auto& it: aThread)
	{
		it.join();
	}
}







