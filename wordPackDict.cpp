#include "pakDataTypes.h"

bool wordPackToXML(const wchar_t* cFilename)
{
	//Load the data from this file
	FILE* f = _wfopen(cFilename, TEXT("rb"));
	if(f == NULL)
	{
		cout << "Unable to open " << cFilename << " for reading." << endl;
		return false;
	}
	
	//Read header
	wordPackDictHeader wpHeader;
	if(fread(&wpHeader, 1, sizeof(wordPackDictHeader), f) != sizeof(wordPackDictHeader))
	{
		cout << "Unable to read wordPackDictHeader." << endl;
		fclose(f);
		return false;
	}
	
	list<wordHeader> whHeaders;
	//Read in wordHeaders
	for(i32 i = 0; i < wpHeader.words.count; i++)
	{
		wordHeader wh;
		if(fread(&wh, 1, sizeof(wordHeader), f) != sizeof(wordHeader))
		{
			cout << "Unable to read wordHeader " << i << endl;
			fclose(f);
			return false;
		}
		whHeaders.push_back(wh);
	}
	
	//Now read in string table
	//Now for string table header
	StringTableHeader sth;
	if(fread((void*)&sth, 1, sizeof(StringTableHeader), f) != sizeof(StringTableHeader))
	{
		cout << "StringTableHeader malformed" << endl;
		fclose(f);
		return false;
	}
	
	vector<StringTableEntry> stringTableList;
	vector<StringPointerEntry> stringPointerList;
	vector<wchar_t> stringList;
	
	//Allocate memory for this many wstring table & pointer entries
	stringTableList.reserve(sth.numStrings);
	stringPointerList.reserve(sth.numPointers);
	stringList.reserve((sizeof(wchar_t) * sth.numStrings)*256);
	
	//Read in string table entries
	for(int i = 0; i < sth.numStrings; i++)
	{
		StringTableEntry ste;
		if(fread((void*)&ste, 1, sizeof(StringTableEntry), f) != sizeof(StringTableEntry))
		{
			cout << "StringTableEntry " << i << " malformed out of " << sth.numStrings << endl;
			fclose(f);
			return false;
		}
		//Store
		stringTableList[i] = ste;
	}
	
	//and string table pointers
	for(int i = 0; i < sth.numPointers; i++)
	{
		StringPointerEntry spe;
		if(fread((void*)&spe, 1, sizeof(StringPointerEntry), f) != sizeof(StringPointerEntry))
		{
			cout << "StringPointerEntry malformed" << endl;
			fclose(f);
			return false;
		}
		//Store
		stringPointerList[i] = spe;
	}
	
	//Now read in the strings until we hit the end of the file
	int c;
	while((c = fgetc(f)) != EOF)
		stringList.push_back(c);
		
	//Save to XML
	XMLDocument doc;
	XMLElement* root = doc.NewElement("words");	//Create the root element
	//root->SetAttribute("num", whHeaders.size());
	
	for(list<wordHeader>::iterator i = whHeaders.begin(); i != whHeaders.end(); i++)
	{
		wchar_t* cData = stringList.data();
		wstring sWord = &cData[stringPointerList[stringTableList[i->wordStrId].pointerIndex].offset];
		
		XMLElement* elem = doc.NewElement("word");
		//elem->SetAttribute("id", i->wordStrId);
		elem->SetAttribute("str", ws2s(sWord).c_str());
		elem->SetAttribute("probability", i->probability);
		root->InsertEndChild(elem);
	}
	
	doc.InsertFirstChild(root);
	wstring sFilename = cFilename;
	sFilename += TEXT(".xml");
	doc.SaveFile(ws2s(sFilename).c_str());
	
	fclose(f);
	
	return true;
}

typedef struct
{
	wstring word;
	f32 probability;
} WordPakHelper;

bool XMLToWordPack(const wchar_t* cFilename)
{
	wstring sXMLFile = cFilename;
	sXMLFile += TEXT(".xml");
	
	XMLDocument doc;
	int iErr = doc.LoadFile(ws2s(sXMLFile).c_str());
	if(iErr != XML_NO_ERROR)
	{
		cout << "Error parsing XML file " << ws2s(sXMLFile) << ": Error " << iErr << endl;
		return false;
	}
	//Grab root element
	XMLElement* root = doc.RootElement();
	if(root == NULL)
	{
		cout << "Root element NULL in XML file " << ws2s(sXMLFile) << endl;
		return false;
	}
	
	//Roll through child elements
	vector<WordPakHelper> vWordPakList;
	XMLElement* elem = root->FirstChildElement();
	while(elem != NULL)
	{
		WordPakHelper wph;
		const char* cStr = elem->Attribute("str");
		if(cStr == NULL)
		{
			cout << "Missing \"str\" attribute for word in " << ws2s(sXMLFile) << endl;
			return false;
		}
		wph.word = s2ws(cStr);
		int iErr = elem->QueryFloatAttribute("probability", &wph.probability);
		if(iErr != XML_NO_ERROR)
		{
			cout << "Error getting \"probability\" for word " << ws2s(wph.word) << " in XML file " << ws2s(sXMLFile) << ": Error " << iErr << endl;
			return false;
		}
		vWordPakList.push_back(wph);	//Hang onto this
		elem = elem->NextSiblingElement();	//Next item
	}
	
	//Write the data to this file
	FILE* f = _wfopen(cFilename, TEXT("wb"));
	if(f == NULL)
	{
		cout << "Unable to open " << cFilename << " for writing." << endl;
		return false;
	}
	size_t curOffset = sizeof(wordPackDictHeader);
	wordPackDictHeader wpdHeader;
	wpdHeader.words.count = vWordPakList.size();
	wpdHeader.words.offset = curOffset;	//Offset this from this header
	wpdHeader.stringTableBytes.count = 0;
	for(unsigned int i = 0; i < vWordPakList.size(); i++)
		wpdHeader.stringTableBytes.count += vWordPakList[i].word.size() + 1;	//Null-terminated, hence the +1
	curOffset += vWordPakList.size() * sizeof(wordHeader);
	wpdHeader.stringTableBytes.offset = curOffset;
	
	//Write the wordPackDictHeader
	fwrite(&wpdHeader, 1, sizeof(wordPackDictHeader), f);
	//Write the wordHeaders
	for(unsigned int i = 0; i < vWordPakList.size(); i++)
	{
		wordHeader wh;
		wh.wordStrId = i;
		wh.probability = vWordPakList[i].probability;
		fwrite(&wh, 1, sizeof(wordHeader), f);
	}
	
	//Write in wstring table header
	StringTableHeader sth;
	sth.numStrings = sth.numPointers = vWordPakList.size();
	fwrite(&sth, 1, sizeof(StringTableHeader), f);
	
	//Write string table entries
	for(unsigned int i = 0; i < vWordPakList.size(); i++)
	{
		StringTableEntry ste;
		ste.pointerIndex = i;
		ste.pointerCount = 1;
		fwrite(&ste, 1, sizeof(StringTableEntry), f);
	}
	
	//Write string pointer entries
	curOffset = 0;
	for(unsigned int i = 0; i < vWordPakList.size(); i++)
	{
		StringPointerEntry spe;
		spe.languageId = LANGID_ENGLISH;
		spe.offset = curOffset;
		curOffset += vWordPakList[i].word.size() + 1;	//Null-terminated, hence the +1
		fwrite(&spe, 1, sizeof(StringPointerEntry), f);
	}
	
	//Now write the strings
	for(unsigned int i = 0; i < vWordPakList.size(); i++)
	{
		fwrite(ws2s(vWordPakList[i].word).c_str(), 1, strlen(ws2s(vWordPakList[i].word).c_str())*sizeof(char), f);
		fwrite("\0", 1, 1, f);	//Null-terminate
	}
	
	fclose(f);
	return true;
}









