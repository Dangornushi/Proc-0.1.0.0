#include "main.hpp"


string parser( string datas, string funcname ) {
    string funcline          ;
    string writed            ;
    string data              ;
    vector < string > defline;
    vector < string > eline  ;
    vector < string > argsv  ;

    if ( datas.find( "{" ) != string::npos ) data = split( split( datas, "fn" )[1], "{" )[0] ; 
    else data = datas;

    string firstw = split( datas, " " )[0];

    defline = split ( data, "->" ) ;
    eline = split ( datas, " " ) ;

    if (  firstw == "fn" ) {
        writed +=  replace ( replace( defline[0], " " ), ":" ) + ":\nfode>" + replace ( defline[1], " " ) + ";\n";
        
        if ( datas.find( "," ) != string::npos ) {
            argsv = split ( split ( split ( replace ( datas, " " ), "(" )[1], ")" )[0], "," ) ;
            for ( int argsvc; argsvc < argsv.size(); argsvc++ ) {
                string argsvd = argsv [ argsvc ] ;
                if ( split ( argsvd, ":" )[0] == "int" ) {
                    writed += "mode>int;\n";
                }
                if ( split ( argsvd, ":" )[0] == "str" ) {
                    writed += "mode>str;\n";
                }
                writed += "pop " + split ( argsvd, ":" )[1] + ";\n" ;
            }
        }
        else {
            writed += "mode>"+split( split ( split ( replace ( datas, " " ), "(" )[1]+",:", ")" )[0], ":" )[0] + ";\npop " + \
                        split( split ( split ( replace ( datas, " " ), "(" )[1]+",:", ")" )[0], ":" )[1] + ";\n";
        }
    }

    if ( firstw == "int" | firstw == "str" && eline[2] == "=" ) {
        if ( eline[0] == "str" ) {
            writed += "mode>str;\n";
        }
        if ( eline[0] == "int" ) {
            writed += "mode>int;\n";
        }
        writed += "mov " + eline[1]+", " + eline[3] + ";\n";
    }

    if ( firstw == "->" ) {
        writed += "call " + split( replace ( datas, " " ), "->" )[1] + ";\n";
    }

    if ( firstw == "msg" ) {
        writed += datas + ";\n";
    }

    if ( firstw == "return" ) {
        writed += "ret " + funcname + ", " + eline[1] + ";\nend;\n\n";
    }

    return writed ;
}


int main( int argc, char **arg ) {
    string data                   ;
    string writedata              ;
    string filename = arg[1]      ;
    string ifsname  = filename    ;
    string ofsname  = filename+"s";
    string incdata                ;
    string funcname = ""          ;

    ifstream ifs ( ifsname );
    ofstream ofs ( ofsname );

    while( getline( ifs, data ) ) {
        if ( data.find( "@include" ) != string::npos ) {
            ifstream incl ( split ( data, " " )[1] ) ;
            while ( getline ( incl, incdata ) ) {
                incdata = replace( incdata, "    " ) ;
                if ( incdata.find ( "fn" ) != string::npos ) {
                    funcname = split( split ( incdata, " " )[1], "(" )[0] ;
                }
                writedata += parser ( incdata, funcname ) ;
            }
        }
        if ( data.find ( "fn" ) != string::npos ) {
            funcname = split( split ( data, " " )[1], "(" )[0] ;
        }
        data = replace ( data, "    " ) ;
        writedata += parser ( data, funcname ) ;
    }

    ofs << writedata ;

    return 0;
}