#include "main.hpp"
    map<string, int> intvall;


string edit( string name, string data, map<string, string> funcs, string maindata, int whilen, map<string, int>intvall ) {
    string maindata2, whilevall, splitdata;
    int c = 0;
//    filewrite( data, name );

    if ( data.find( ":" ) != string::npos ) {
        maindata += "\n"+split( data, ":")[0]+":\n";
        maindata += split( data, ":")[1]+";\n";
    }

    else {
        if ( data.find( "jmp" ) == string::npos ) {
            maindata += data+";\n";
        }
        if ( data.find( "call" ) != string::npos ) {
            string fna = split( split( data, "call " )[1], "[" )[0];
            for ( int ii = 0; ii <  split( funcs[ fna ], ";" ).size(); ++ ii ) {
                maindata += edit( name, split( funcs[ fna ], ";" )[ii], funcs, maindata2, whilen, intvall);
            }
        }

        if ( data.find( "jmp" ) != string::npos ) {
            string fna = split( split( data, "jmp " )[1], "(" )[0];
            string whiledata = regex_replace( split( split( funcs[fna], ":" )[1], ";ret" )[0], regex( ";" ), ";\n" );
            maindata += "\n";
            for ( int ii = 0; ii <  split( funcs[ fna ], ";" ).size(); ++ ii ) {
                splitdata += edit( name, split( funcs[ fna ], ";" )[ii], funcs, maindata2, whilen, intvall);
            }

            for (int i = 0; i < whilen-1; i++) {
                maindata += whiledata+";\n";
            }

            maindata += split( splitdata, ":" )[1]+"\n";

        }

    }
    return maindata;
}

string ifrun( vector<string> vec, string movd, string name, string wdata, string maindata, int whilen, map<string, string> funcs ) {
    string wdata2;
    
    vec = split( funcs[ split( movd, ", " )[2] ], ";" ) ;
    for ( int i = 0; i < vec.size(); i++ ) {
        if ( vec[i].find(":") != string::npos ) { vec[i] = split( vec[i], ":" )[1]; }
        wdata2 += edit( name, vec[i], funcs, maindata, whilen, intvall );
    }
    wdata += split( wdata2, ":" )[0]+split( wdata2, ":" )[1];
    wdata = regex_replace( wdata, regex( movd+";" ), "" );
    return wdata;
}

int main( int argc, char **arg ) {
    string data, name = arg[1], funcname, callname, calls, maindata, wdata, wdata2, movd;
    ifstream ifs( name+"s");
    map< string, string > funcs;
    map<string, string> whilemap;
    map<string, int> intvall;
    vector <string> vec;
    vector <string> vec2;
    int fuj = 0, whilec = 0, whilen = 0;
    ofstream ofs ( split( name, "." )[0]+".del" );

    while ( getline( ifs, data ) ) {
        if ( data.find( ":" ) != string::npos ) {
            funcname = split( data, "(" )[0];
            if ( funcname.find( "," ) != string::npos ) {
                whilemap[funcname] += data; 
                whilec = 1;
                whilen = atoi( split( funcname, ", " )[1].c_str() );
            }
            funcs[funcname] += data;
        }
        else {
            if ( whilec == 1 ) {
                whilemap[ funcname ] += data;
            }
            funcs[ funcname ] += data;
        }
    }

    vec = split( funcs[ "main" ], ";" );
    for ( int i = 0; i < vec.size(); ++i ) {
        wdata += edit( name, vec[i], funcs, maindata, whilen, intvall );
    }

    vec2 = split( wdata, ";" );
    for ( int i = 0; i < vec2.size(); ++i ) {
        movd = replace( vec2[i], "\n" );
        if ( movd.find( "mov" ) !=string::npos ) {
            intvall[ split( split( movd, "," )[0], " " )[1] ] = atoi( split(movd, ", ")[1].c_str() );
        }
        if ( movd.find( "jae" ) != string::npos ) {
            string x = split( split( movd, "," )[0], " " )[1];
            string y = split( movd, ", " )[1];
            if ( intkeyfind( intvall, x ) ) {
                if ( intvall[x] == atoi( y.c_str() ) ) {
                    vec.clear();
                    wdata = ifrun ( vec, movd, name, wdata, maindata, whilen, funcs );
                }
            }
        }
        if ( movd.find( "jnp" ) != string::npos ) {
            string x = split( split( movd, "," )[0], " " )[1];
            string y = split( movd, ", " )[1];
            if ( intkeyfind( intvall, x ) ) {
                if ( intvall[x] > atoi( y.c_str() ) ) {
                    vec.clear();
                    wdata = ifrun ( vec, movd, name, wdata, maindata, whilen, funcs );
                }
            }
        }
        if ( movd.find( "ja" ) != string::npos ) {
            string x = split( split( movd, "," )[0], " " )[1];
            string y = split( movd, ", " )[1];
            if ( intkeyfind( intvall, x ) ) {
                if ( intvall[x] < atoi( y.c_str() ) ) {
                    vec.clear();
                    wdata = ifrun ( vec, movd, name, wdata, maindata, whilen, funcs );
                }
            }
        }
    }

    ofs << wdata << flush;
    ofs.close();
    return 0;
}

//u22
