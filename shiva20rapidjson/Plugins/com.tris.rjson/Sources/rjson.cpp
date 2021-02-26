//-----------------------------------------------------------------------------
#include "PrecompiledHeader.h"
#include "rjson.h"
//-----------------------------------------------------------------------------
#include <memory>

#include "C_rjson.h"
std::unique_ptr<C_rjson> SJS(new C_rjson);


#ifdef S3DX_DLL
	rjsonAPI rjson ;
#endif

//-----------------------------------------------------------------------------
//  Callbacks
//-----------------------------------------------------------------------------

int Callback_rjson_getArraySize ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "rjson.getArraySize" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sID         = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sKeyToArray = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nSizeOrNil ;

	nSizeOrNil = SJS->getArraySize(sID.GetStringValue(), sKeyToArray.GetStringValue());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nSizeOrNil ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_rjson_init ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "rjson.init" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nReserve = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SJS->init(nReserve.GetNumberValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_rjson_loadString ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "rjson.loadString" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sID   = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sJSON = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	bOK.SetBooleanValue(SJS->loadString(sID.GetStringValue(), sJSON.GetStringValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_rjson_hasValue ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "rjson.hasValue" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sID  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sKey = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bYes ;

	bYes.SetBooleanValue(SJS->hasValue(sID.GetStringValue(), sKey.GetStringValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bYes ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_rjson_getValue ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "rjson.getValue" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sID  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sKey = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable vValue ;

	vValue = SJS->getValue(sID.GetStringValue(), sKey.GetStringValue());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = vValue ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_rjson_hasKey ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "rjson.hasKey" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sID  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sKey = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bYes ;

	bYes.SetBooleanValue(SJS->hasKey(sID.GetStringValue(), sKey.GetStringValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bYes ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------
//  Constructor / Destructor
//-----------------------------------------------------------------------------

rjsonPackage::rjsonPackage ( )
{
#ifdef S3DX_DLL
    rjson.pfn_rjson_getArraySize = Callback_rjson_getArraySize ;
    rjson.pfn_rjson_init       = Callback_rjson_init       ;
    rjson.pfn_rjson_loadString = Callback_rjson_loadString ;
    rjson.pfn_rjson_hasValue   = Callback_rjson_hasValue   ;
    rjson.pfn_rjson_getValue   = Callback_rjson_getValue   ;
    rjson.pfn_rjson_hasKey     = Callback_rjson_hasKey     ;
	
#endif
}

//-----------------------------------------------------------------------------

rjsonPackage::~rjsonPackage ( )
{

}

//-----------------------------------------------------------------------------
//  Functions table
//-----------------------------------------------------------------------------

static S3DX::AIFunction aMyFunctions [ ] =
{
    { "getArraySize", Callback_rjson_getArraySize, "nSizeOrNil", "sID, sKeyToArray", "checks if a key refers to an array and returns its size if so", 0 }, 
    { "init"      , Callback_rjson_init      , "bOK"   , "nReserve"  , "inits plugin and reserves nReserve JSON doc slots", 0 }, 
    { "loadString", Callback_rjson_loadString, "bOK"   , "sID, sJSON", "loads sJSON string and stores it under sID"       , 0 }, 
    { "hasValue"  , Callback_rjson_hasValue  , "bYes"  , "sID, sKey" , "checks if a value for sKey in sID exists"         , 0 }, 
    { "getValue"  , Callback_rjson_getValue  , "vValue", "sID, sKey" , "returns value for sKey in sID"                    , 0 }, 
    { "hasKey"    , Callback_rjson_hasKey    , "bYes"  , "sID, sKey" , "checks if sKey in sID exists"                     , 0 }    
    //{ NULL, NULL, NULL, NULL, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Constants table
//-----------------------------------------------------------------------------

static S3DX::AIConstant aMyConstants [ ] =
{
	{ NULL, 0, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Accessors
//-----------------------------------------------------------------------------

const char *rjsonPackage::GetName ( ) const
{
    return "rjson" ;
}

//-----------------------------------------------------------------------------

S3DX::uint32 rjsonPackage::GetFunctionCount ( ) const
{
	if ( aMyFunctions[0].pName == NULL )
	{
		return 0 ;
	}
	else
	{
		return sizeof( aMyFunctions ) / sizeof( S3DX::AIFunction ) ;
	}
}

//-----------------------------------------------------------------------------

S3DX::uint32 rjsonPackage::GetConstantCount ( ) const
{
	if ( aMyConstants[0].pName == NULL )
	{
		return 0 ;
	}
	else
	{
		return sizeof( aMyConstants ) / sizeof( S3DX::AIConstant ) ;
	}
}

//-----------------------------------------------------------------------------

const S3DX::AIFunction *rjsonPackage::GetFunctionAt ( S3DX::uint32 _iIndex ) const
{
    return &aMyFunctions[ _iIndex ] ;
}

//-----------------------------------------------------------------------------

const S3DX::AIConstant *rjsonPackage::GetConstantAt ( S3DX::uint32 _iIndex ) const
{
    return &aMyConstants[ _iIndex ] ;
}
