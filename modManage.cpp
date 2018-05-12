#include <chrono>
#include "pakDataTypes.h"
#include "stringTools.h"

#define RESOURCE_1_NAME	L"resource.pak"
#define RESOURCE_2_NAME	L"embed.pak"
#define RESOURCE_3_NAME	L"frontend.pak"

map<u32, virtualFile> g_mOrig;
map<u32, virtualFile> g_mMods;
list<resourceHeader> g_lResourceHeaders[3];
ofstream oWarnings("mergeresults.txt");

void splitOutFiles(FILE* f, list<resourceHeader>* lRH, bool bMod)
{
	//Iterate through these items, splitting them out of the file and saving the data
	for(list<resourceHeader>::iterator i = lRH->begin(); i != lRH->end(); i++)
	{
		fseek(f, i->offset, SEEK_SET);
		
		uint8_t* buf = (uint8_t*)malloc(i->size);
	  
		if(fread((void*)buf, 1, i->size, f) != i->size)
		{
			cout << "Error reading non-compressed data." << endl;
			fclose(f);
			//fclose(fOut);
			free(buf);
			continue;
		}
		virtualFile vf;
		vf.size = i->size;
		vf.data = buf;
		if(bMod)
		{
			if(g_mMods.count(i->id))	//This was here already
			{
				//TODO: Merge residmap.dat files together
				oWarnings << "Warning: Conflict with mod resource " << i->id << ". Overwriting..." << endl;
				free(g_mMods[i->id].data);	//Clean up original memory
			}
			g_mMods[i->id] = vf;
		}
		else
		{
			if(g_mOrig.count(i->id))	//This was here already
			{
				oWarnings << "Warning: Conflict with original resource " << i->id << ". Overwriting..." << endl;
				free(g_mOrig[i->id].data);	//Clean up original memory
			}
			g_mOrig[i->id] = vf;
		}
	}
}

void copyTempFiles()
{
	for(map<u32, virtualFile>::iterator i = g_mMods.begin(); i != g_mMods.end(); i++)
	{
		if(g_mOrig.count(i->first))	//Original file here already
		{
			oWarnings << "Note: Mod overwriting original resource: " << i->first << endl;
			free(g_mOrig[i->first].data);	//Clean up this memory
		}
		else	//We're copying in a new file. Stick it in embed.pak for now. TODO: Some sort of selection
		{
			resourceHeader rH;
			rH.id = i->first;	//Only need the ID, the rest will be filled in later
			if(rH.id != RESIDMAP_ID)
				//g_lResourceHeaders[1].push_front(rH);	//TODO: pakfile selection
			//else
				g_lResourceHeaders[1].push_back(rH);
		}
		g_mOrig[i->first] = i->second;
	}
}

//Main program entry point
int main(int argc, char** argv)
{
	auto start = std::chrono::high_resolution_clock::now();
	
	if(argc < 2)
	{
		cout << "Usage: modManage [pakfile1] [pakfile2] ... [pakfileN]" << endl;
		return 0;
	}
	
	//First, check and see what resource ID's are in each mod to merge, and split them all out
	list<resourceHeader> lModResHeaders[argc-1];	//For splitting mods out of the .pak files
	map<u32, u32> mModHeader;	//For repacking, need to know the flags for this file
	map<u32, bool> mModResources;
	for(int iArg = 1; iArg < argc; iArg++)
	{
		//Read in these files
		cout << "Unpacking mod " << argv[iArg] << endl;
		FILE* f = fopen(argv[iArg], "rb");
		if(f == NULL)
		{
			cout << "Unable to open file " << argv[iArg] << endl;
			continue;
		}
		
		blobHeader bH;
		if(fread((void*)&bH, 1, sizeof(blobHeader), f) != sizeof(blobHeader))
		{
			cout << "Error reading number of resources in file " << argv[iArg] << endl;
			fclose(f);
			continue;
		}
		
		for(int i = 0; i < bH.numItems; i++)
		{
			resourceHeader rH;
			size_t sizeRead = fread((void*)&rH, 1, sizeof(resourceHeader), f);
			if(sizeRead != sizeof(resourceHeader))
			{
				cout << "Read " << sizeRead << " bytes, which differs from resource header size " << sizeof(resourceHeader) << endl;
				fclose(f);
				continue;
			}
			lModResHeaders[iArg-1].push_back(rH);
			mModResources[rH.id] = true;
			mModHeader[rH.id] = rH.flags;
		}
		
		splitOutFiles(f, &lModResHeaders[iArg-1], true);
		
		fclose(f);
	}
	
	bool bPack[3];
	
	//Now that we have all the resources from the mod .pak files unpacked, check and see what original .pak files need to be changed
	for(int iPak = 0; iPak < 3; iPak++)
	{
		wstring sArg;
		
		switch(iPak)
		{
			case 0:
				sArg = RESOURCE_1_NAME;
				break;
			case 1:
				sArg = RESOURCE_2_NAME;
				break;
			default:
				sArg = RESOURCE_3_NAME;
				break;
		}
		
		cout << "Pulling headers from resource blob file " << ws2s(sArg) << endl;
		FILE* f = fopen(ws2s(sArg).c_str(), "rb");
		if(f == NULL)
		{
			cout << "Unable to open file " << ws2s(sArg) << endl;
			continue;
		}
		
		blobHeader bH;
		if(fread((void*)&bH, 1, sizeof(blobHeader), f) != sizeof(blobHeader))
		{
			cout << "Error reading number of resources in file " << ws2s(sArg) << endl;
			fclose(f);
			continue;
		}
		
		bPack[iPak] = false;
		if(iPak == 1)	//TODO: Stick new files in other .pak files instead of embed.pak
			bPack[iPak] = true;	//TODO: Actually test to see if new files, and in what pakfiles
		
		for(int i = 0; i < bH.numItems; i++)
		{
			resourceHeader rH;
			size_t sizeRead = fread((void*)&rH, 1, sizeof(resourceHeader), f);
			if(sizeRead != sizeof(resourceHeader))
			{
				cout << "Read " << sizeRead << " bytes, which differs from resource header size " << sizeof(resourceHeader) << endl;
				fclose(f);
				continue;
			}
			g_lResourceHeaders[iPak].push_back(rH);
			
			if(mModResources.count(rH.id))
				bPack[iPak] = true;
		}
		
		if(bPack[iPak])	//Unpack this resource only if we need to
		{
			cout << "Unpacking resource " << ws2s(sArg) << endl;
			splitOutFiles(f, &g_lResourceHeaders[iPak], false);
		}
		
		fclose(f);
	}
	
	//Now we have all the .pak files we need extracted. Copy mod files over
	copyTempFiles();
	
	//And recompress
	for(int iPak = 0; iPak < 3; iPak++)
	{
		if(!bPack[iPak])
			continue;
		wstring sArg;
		
		switch(iPak)
		{
			case 0:
				sArg = RESOURCE_1_NAME;
				break;
			case 1:
				sArg = RESOURCE_2_NAME;
				break;
			default:
				sArg = RESOURCE_3_NAME;
				break;
		}
		
		cout << "Repacking resource blob file " << ws2s(sArg) << endl;
		
		//Open our output pakfile for writing
		FILE* f = fopen(ws2s(sArg).c_str(), "wb");
		if(f == NULL)
		{
			cout << "Unable to open file " << ws2s(sArg) << " for writing. Skipping..." << endl;
			continue;
		}
		
		//Add the header
		blobHeader bh;
		bh.pakVersion = 0x01;
		bh.numItems = g_lResourceHeaders[iPak].size();
		
		fwrite(&bh, 1, sizeof(blobHeader), f);
		
		//Get the starting file pos for where we (should) be writing objects to
		size_t offsetPos = sizeof(blobHeader) + (g_lResourceHeaders[iPak].size() * sizeof(resourceHeader));	
		
		//Add the table of contents
		cout << "Adding table of contents..." << endl;
		for(list<resourceHeader>::iterator i = g_lResourceHeaders[iPak].begin(); i != g_lResourceHeaders[iPak].end(); i++)
		{			
			i->offset = offsetPos;	//Offset
			i->size = g_mOrig[i->id].size;	//Size of file
			if(mModHeader.count(i->id))
				i->flags = mModHeader[i->id];	//Set the flags to the flags of this file copied over (otherwise keep the same flags)
			
			fwrite(&(*i), 1, sizeof(resourceHeader), f);	//Write this to the file
			
			offsetPos += i->size;	//Add this size to our running tally of where we are
		}
		
		//Add actual resource data
		cout << "Adding files..." << endl;
		for(list<resourceHeader>::iterator i = g_lResourceHeaders[iPak].begin(); i != g_lResourceHeaders[iPak].end(); i++)
		{			
			virtualFile vfIn = g_mOrig[i->id];
			if(vfIn.data == NULL)
			{	
				cout << "Error: resource " << i->id << " is in more than one output .pak file. Abort." << endl;
				return 1;
			}
			
			//cout << "Merging " << i->id << endl;
			
			fwrite(vfIn.data, 1, vfIn.size, f);	//Write this to the file
			
			//Free this data while we're at it
			free(vfIn.data);
			g_mOrig[i->id].data = NULL;
		}
		fclose(f);	//Done packing this .pak file
	}	
	//Done
	cout << endl << "Done." << endl;
	
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::minutes>(end - start);
	
	cout << "Time elapsed: " << duration.count() << " min" << endl;

	oWarnings << "Done." << endl;
	oWarnings.close();
	return 0;
}