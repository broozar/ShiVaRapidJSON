#pragma once

// STL
#include <unordered_map>

//rapidjson
#include "document.h"
using namespace rapidjson;


class C_rjson {

private:
	std::unordered_map<const char*, Document> _jsonIDs;
	bool _doesIDexist(const char* sID) const;
	const Value& _travelDown(const Value& doc, std::vector<std::string>* segments, int & size, int & interation, const Value& defaultReturn);
	S3DX::AIVariable _JsonValToAIVar(const Value& val);


public:

	// init
	C_rjson();
	~C_rjson();
	bool init(float&& res);

	// create document
	bool loadString(const char* sID, const char* sJSON);

	// checks
	bool hasKey(const char* sID, const char* sKey);
	bool hasValue(const char* sID, const char* sKey);

	// get
	S3DX::AIVariable C_rjson::getValue(const char * sID, const char * sKey);
	S3DX::AIVariable C_rjson::getArraySize(const char * sID, const char * sKey);

};
