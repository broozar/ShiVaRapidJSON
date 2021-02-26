#include "PrecompiledHeader.h"
#include "C_rjson.h"

// stl
#include <sstream>
#include <string>


C_rjson::C_rjson() {}
C_rjson::~C_rjson() {}


// privates ---------------------------------------------

const Value& C_rjson::_travelDown(const Value& doc, std::vector<std::string>* segments, int & size, int & iteration, const Value& defaultReturn) {

	auto str = (*segments)[iteration];
	auto cstr = str.c_str();

	// handle array indices of form ?number
	if (str.at(0) == '?') {
		auto newnum = std::stoi(str.erase(0, 1));

		// array security checks
		if (!doc.IsArray()) {
			S3DX::log.warning("RapidJSON: Element is not an array (via _travelDown).");
			return defaultReturn;
		}
		if (((int)doc.Size() - newnum) < 1) {
			S3DX::log.warning("RapidJSON: Array element out of bounds (via _travelDown).");
			return defaultReturn;
		}

		const Value& newval = doc[SizeType(newnum)];

		// next iteration?
		if ((size - iteration) > 1) {
			// next iteration loop
			++iteration;
			return _travelDown(newval, segments, size, iteration, defaultReturn);
		}
		else {
			return newval;
		}

	}


	// handle non-arrays
	else {
		if (!doc.HasMember(cstr)) {
			S3DX::log.warning("RapidJSON: Invalid key '", cstr, "' (via _travelDown).");
			return defaultReturn;
		}
		else {
			const Value& newval = doc[cstr];

			// next iteration?
			if ((size - iteration) > 1) {
				// next iteration loop
				++iteration;
				return _travelDown(newval, segments, size, iteration, defaultReturn);
			}
			else {
				return newval;
			}

		}
	}
}

bool C_rjson::_doesIDexist(const char * sID) const {
	if (_jsonIDs.find(sID) == _jsonIDs.end()) {
		S3DX::log.warning("RapidJSON: Document '", sID, "' not found!");
		return false;
	}

	return true;
}

S3DX::AIVariable C_rjson::_JsonValToAIVar(const Value & val) {

	// output
	S3DX::AIVariable out;
	out.SetNil();

	/*
	// debug type check
	switch (val.GetType()) {
	case 0: S3DX::log.message("T Null"); break;
	case 1: S3DX::log.message("T false"); break;
	case 2: S3DX::log.message("T true"); break;
	case 3: S3DX::log.message("T obj"); break;
	case 4: S3DX::log.message("T arr"); break;
	case 5: S3DX::log.message("T str"); break;
	case 6: S3DX::log.message("T num"); break;
	}
	*/

	// RETURNS ---------------
	// bool
	if (val.IsBool())			out.SetBooleanValue(val.GetBool());
	// string
	else if (val.IsString())	out.SetStringValue(val.GetString());
	// number - Lua only takes floats... time for lossy conversion
	else if (val.IsFloat())		out.SetNumberValue(val.GetFloat());
	else if (val.IsDouble())	out.SetNumberValue((float)val.GetDouble());
	else if (val.IsInt())		out.SetNumberValue((float)val.GetInt());
	else if (val.IsInt64())		out.SetNumberValue((float)val.GetInt64());
	else if (val.IsUint())		out.SetNumberValue((float)val.GetUint());
	else if (val.IsUint64())	out.SetNumberValue((float)val.GetUint64());
	// table - placeholder
	else if (val.IsArray())		out.SetStringValue("JSON_ARRAY");
	// object - placeholder
	else if (val.IsObject())	out.SetStringValue("JSON_OBJECT");
	// NULL / nil
	else if (val.IsNull())		out.SetNil();
	// nil
	else S3DX::log.warning("RapidJSON: Value has unknown type.");

	return out;
}


// publics ---------------------------------------------

bool C_rjson::init(float && res) {
	auto r = (INT)res;
	if (r > 0) _jsonIDs.reserve(r);
	else {
		_jsonIDs.reserve(8);
		S3DX::log.warning("RapidJSON: Call INIT with reserve values >0 please!");
	}
	return true;
}

bool C_rjson::loadString(const char * sID, const char * sJSON) {

	if ((sID == nullptr) || (sID[0] == '\0')) {
		S3DX::log.warning("RapidJSON: loadString IDs cannot be empty.");
		return false;
	}

	//Document doc;
	
	if (_jsonIDs[sID].Parse(sJSON).HasParseError()) {
		S3DX::log.warning("RapidJSON: loadString '", sID, "' has created parsing errors.");
		return false;
	}

	// everything went fine
	return true;
}

bool C_rjson::hasKey(const char * sID, const char * sKey) {
	if (!this->_doesIDexist(sID)) return false;

	const Value& document = _jsonIDs.at(sID);
	if (!document.IsObject()) {
		S3DX::log.warning("RapidJSON: '", sID, "' is not a proper document object (via hasKey).");
		return false;
	}

	// explode input
	std::stringstream ssin(sKey);
	std::string sspart;
	std::vector<std::string> ssparts;

	while (std::getline(ssin, sspart, ',')) {
		ssparts.push_back(sspart);
	}
	int ssize = ssparts.size();

	// recursive call
	int iter = 0;
	Value val; // returns default null
	const Value& pkey = _travelDown(document, &ssparts, ssize, iter, val);

	if (pkey.IsNull()) return false;
	
	return true;
}

bool C_rjson::hasValue(const char * sID, const char * sKey) {
	if (!this->_doesIDexist(sID)) return false;

	const Value& document = _jsonIDs.at(sID);
	if (!document.IsObject()) {
		S3DX::log.warning("RapidJSON: '", sID, "' is not a proper document object (via hasValue).");
		return false;
	}

	// explode input
	std::stringstream ssin(sKey);
	std::string sspart;
	std::vector<std::string> ssparts;

	while (std::getline(ssin, sspart, ',')) {
		ssparts.push_back(sspart);
	}
	int ssize = ssparts.size();

	// recursive call
	int iter = 0;
	Value val; // returns default null
	const Value& pkey = _travelDown(document, &ssparts, ssize, iter, val);

	S3DX::AIVariable out;
	out = _JsonValToAIVar(pkey);
	if (out.IsNil()) return false;

	return true;
}

S3DX::AIVariable C_rjson::getValue(const char * sID, const char * sKey) {

	// output storage
	S3DX::AIVariable out;
	out.SetNil();

	// existence checks
	if (!this->_doesIDexist(sID)) return out;

	const Value& document = _jsonIDs.at(sID);
	if (!document.IsObject()) {
		S3DX::log.warning("RapidJSON: '", sID, "' is not a proper document object (via getValue).");
		return out;
	}

	// explode input
	std::stringstream ssin(sKey);
	std::string sspart;
	std::vector<std::string> ssparts;

	while (std::getline(ssin, sspart, ',')) {
		ssparts.push_back(sspart);
	}
	int ssize = ssparts.size();

	// recursive call
	int iter = 0;
	Value val; // returns default null
	const Value& pkey = _travelDown(document, &ssparts, ssize, iter, val);

	out = _JsonValToAIVar(pkey);

	return out;
}

S3DX::AIVariable C_rjson::getArraySize(const char * sID, const char * sKey) {
	// output storage
	S3DX::AIVariable out;
	out.SetNil();

	// existence checks
	if (!this->_doesIDexist(sID)) return out;

	const Value& document = _jsonIDs.at(sID);
	if (!document.IsObject()) {
		S3DX::log.warning("RapidJSON: '", sID, "' is not a proper document object (via getArraySize).");
		return out;
	}

	// explode input
	std::stringstream ssin(sKey);
	std::string sspart;
	std::vector<std::string> ssparts;

	while (std::getline(ssin, sspart, ',')) {
		ssparts.push_back(sspart);
	}
	int ssize = ssparts.size();

	// recursive call
	int iter = 0;
	Value val; // returns default null
	const Value& pkey = _travelDown(document, &ssparts, ssize, iter, val);

	if (!pkey.IsNull() && pkey.IsArray()) {
		int asize = pkey.Size();
		out.SetNumberValue((float)asize);
	}

	return out;
}
