//-----------------------------------------------------------------------------
#ifndef __rjson_h__
#define __rjson_h__
//-----------------------------------------------------------------------------
#include "S3DXAIPackage.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Package declaration
//-----------------------------------------------------------------------------
class rjsonPackage : public S3DX::AIPackage
{
public :

    //-------------------------------------------------------------------------
    //  Constructor / Destructor
	//-------------------------------------------------------------------------

	rjsonPackage         ( ) ;
                               ~rjsonPackage         ( ) ;

	//-------------------------------------------------------------------------
    //  Accessors
	//-------------------------------------------------------------------------

    const   char               *GetName             ( ) const ;
            S3DX::uint32        GetFunctionCount    ( ) const ;
            S3DX::uint32        GetConstantCount    ( ) const ;
    const   S3DX::AIFunction   *GetFunctionAt       ( S3DX::uint32 _iIndex ) const ;
    const   S3DX::AIConstant   *GetConstantAt       ( S3DX::uint32 _iIndex ) const ;

} ;

//-----------------------------------------------------------------------------
// Package API declaration
//-----------------------------------------------------------------------------
class rjsonAPI
{
public :

    //-------------------------------------------------------------------------
    //  API Constructor
	//-------------------------------------------------------------------------
                                rjsonAPI       ( ) 
                                {
                                    pfn_rjson_getArraySize = NULL ;
                                    pfn_rjson_init       = NULL ;
                                    pfn_rjson_loadString = NULL ;
                                    pfn_rjson_hasValue   = NULL ;
                                    pfn_rjson_getValue   = NULL ;
                                    pfn_rjson_hasKey     = NULL ;

                                }

	//-------------------------------------------------------------------------
	//  API Callbacks 
	//-------------------------------------------------------------------------

    S3DX::AICallback        pfn_rjson_getArraySize ;
    S3DX::AICallback        pfn_rjson_init ;
    S3DX::AICallback        pfn_rjson_loadString ;
    S3DX::AICallback        pfn_rjson_hasValue ;
    S3DX::AICallback        pfn_rjson_getValue ;
    S3DX::AICallback        pfn_rjson_hasKey ;

	//-------------------------------------------------------------------------
	//  API Functions 
	//-------------------------------------------------------------------------

    inline S3DX::AIVariable     getArraySize ( const S3DX::AIVariable& sID, const S3DX::AIVariable& sKeyToArray ) { S3DX_DECLARE_VIN_02( sID, sKeyToArray ) ; S3DX::AIVariable vOut ; if ( pfn_rjson_getArraySize ) pfn_rjson_getArraySize ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     init       ( const S3DX::AIVariable& nReserve ) { S3DX_DECLARE_VIN_01( nReserve ) ; S3DX::AIVariable vOut ; if ( pfn_rjson_init ) pfn_rjson_init ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     loadString ( const S3DX::AIVariable& sID, const S3DX::AIVariable& sJSON ) { S3DX_DECLARE_VIN_02( sID, sJSON ) ; S3DX::AIVariable vOut ; if ( pfn_rjson_loadString ) pfn_rjson_loadString ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     hasValue   ( const S3DX::AIVariable& sID, const S3DX::AIVariable& sKey ) { S3DX_DECLARE_VIN_02( sID, sKey ) ; S3DX::AIVariable vOut ; if ( pfn_rjson_hasValue ) pfn_rjson_hasValue ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     getValue   ( const S3DX::AIVariable& sID, const S3DX::AIVariable& sKey ) { S3DX_DECLARE_VIN_02( sID, sKey ) ; S3DX::AIVariable vOut ; if ( pfn_rjson_getValue ) pfn_rjson_getValue ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     hasKey     ( const S3DX::AIVariable& sID, const S3DX::AIVariable& sKey ) { S3DX_DECLARE_VIN_02( sID, sKey ) ; S3DX::AIVariable vOut ; if ( pfn_rjson_hasKey ) pfn_rjson_hasKey ( 2, vIn, &vOut ); return vOut ; }

 	//-------------------------------------------------------------------------
	//  API Constants 
	//-------------------------------------------------------------------------


} ;

extern rjsonAPI rjson;

//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
