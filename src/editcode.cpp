#include "main.hpp"


string edit( string name, string data, map<string, string> funcs, string maindata, int whilen ) {
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
                maindata += edit( name, split( funcs[ fna ], ";" )[ii], funcs, maindata2, whilen);
            }
        }
        if ( data.find( "jmp" ) != string::npos ) {
            string fna = split( split( data, "jmp " )[1], "(" )[0];
            string whiledata = regex_replace( split( split( funcs[fna], ":" )[1], ";ret" )[0], regex( ";" ), ";\n" );
            maindata += "\n";
            for ( int ii = 0; ii <  split( funcs[ fna ], ";" ).size(); ++ ii ) {
                splitdata += edit( name, split( funcs[ fna ], ";" )[ii], funcs, maindata2, whilen);
            }

            //maindata += split( splitdata, ":" )[0]+":\n\n";

            for (int i = 0; i < whilen-1; i++) {
                maindata += whiledata+";\n";
            }

            maindata += split( splitdata, ":" )[1]+"\n";

        }
    }
    return maindata;
}


int main( int argc, char **arg ) {
    string data, name = arg[1], funcname, callname, calls, maindata, wdata;
    ifstream ifs( name+"s");
    map< string, string > funcs;
    map<string, string> whilemap;
    vector <string> vec;
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
        wdata += edit( name, vec[i], funcs, maindata, whilen );
    }
    ofs << wdata << flush;
    ofs.close();
    return 0;
}

//u22

/*
　人人人人人人人人人
＞明日絶対完成させる＜
　YVYVYVYVYVYVYV
*/