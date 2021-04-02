#include "main.hpp"

void VM ( map<string, string> func, string funcname, map <string, int> intvall, map <string, string> strvall, int loopj ) {
    vector<string> vec = split( func[funcname], "3b" ), vec2, vec3;
    map <string, string> strin;
    string vdata, ans, a, b, mode, fode, anser;
    stringstream ss, ss2;

    int y, x, popc=-1, callc=0;
    for ( int i = 0; i < vec.size(); i++ ) {
        vdata = vec[i];
        vdata = regex_replace( vdata, regex("22"),"20");
        if ( vdata != "" ) {
            if ( vdata.find( "61646420" ) != string::npos ) {
                string mark = "616464" ;
                intvall = calcproc( intvall, mark, mode, vdata );
            }
            
            if ( vdata.find( "73756200" ) != string::npos ) {
                // TODO : This is sub / [-]
                string base = replace( vdata, "73756200" );
                string ans = strpri( split( base, "2c20" )[0] );
                string vall = strpri( split( base, "2c20" )[1] );
                if ( intkeyfind( intvall, vall ) != true ) {
                    intvall[ans] = intvall[ans] - atoi( vall.c_str() ) - loopj;
                }
            }
            
            if ( vdata.find( "6d756c20" ) != string::npos ) {
                string mark = "6d756c";
                intvall = calcproc( intvall, mark, mode, vdata );
            }

            if ( vdata.find( "64697620" ) != string::npos ) {
                string mark = "646976";
                intvall = calcproc( intvall, mark, mode, vdata );
            }
            if ( vdata.find( "6d736720" ) != string::npos ) {
                if ( keyfind( strvall, strpri( split( vdata, "6d736720" )[1] )  ) &&
                    intkeyfind(intvall, strpri( split( vdata, "6d736720" )[1] )  ) == false ) {
                    cout << strvall[ strpri( split( vdata, "6d736720" )[1] ) ] << endl;
                }
                else {
                    if ( intvall[ strpri( split( vdata, "6d736720" )[1] ) ] != 0 ) {
                        cout << intvall[ strpri( split( vdata, "6d736720" )[1] ) ] << endl;
                    }
                    else {
                        cout << strvall[ strpri( split( vdata, "6d736720" )[1] ) ] << endl;
                    }
                }
            }

            if ( vdata.find( "6d6f7620" ) != string::npos ) {
                /*
                TODO : This is mov
                */
                string data, a;
                ans = strpri( split( split( vdata, "2c20" )[0], "6d6f7620" )[1] );
                a = split( vdata, "2c20" )[1];
                data = strpri( a );
                if( mode == "int" ) {
                    if ( intkeyfind ( intvall, data ) ) {
                        intvall[ans] = intvall[ data ];
                    }
                    else {
                        intvall[ans] = atoi( data.c_str() );
                    }
                }
                else
                if ( mode == "str" ) {
                    strvall[ans] = data;
                }
            }
            if ( vdata.find( "6d6f64653e" ) != string::npos ) {
                if ( split( vdata, "6d6f64653e" )[1] == "696e74" ) {
                    mode = "int";
                }
                else
                if ( split( vdata, "6d6f64653e" )[1] == "737472" ) {
                    mode = "str";
                }
            }
            if ( vdata.find( "63616c6c" ) != string::npos ) {
                /* TODO : This is "call"
                ？　（　より前の語句のみ格納されている、つまり呼び出しには　（　より前でのみ読み読み込みされれば良い。
                ？　（　よりあとかつ　）　の前での語句のみを独自に読み取り変数の受け渡しに使用
                ？　ただしそれには呼び出し時に引数を記述しなければならない
                ？　⇨　base : callを抜き出したもともとの文字列、呼び出し文
                ？　⇨　func : 呼び出しされる関数名
                ？　⇨　 arg : 受け渡される変数名が加わる文字列
                */
                string arg = split( split( vdata, "5d" )[0], "5b" )[1], arg2;
                vector<string> vec;
                map<string, int>intvall2;
                map<string, string>strvall2;
                if ( arg.find( "2c" ) != string::npos ) {
                    vec = split( arg, "2c" );
                    for ( int i = 0; i < vec.size(); i++ ) {
                        vec[i] = strpri(vec[i]);
                        strvall2[ to_string(i) ] = strvall[ vec[i] ] ;
                        intvall2[ to_string(i) ] = intvall[ vec[i] ] ;
                    }
                }
                else {
                    arg2 = strpri( arg );
                    strvall2 [ to_string( callc ) ] = strvall [ arg2 ] ;
                    intvall2 [ to_string( callc ) ] = intvall [ arg2 ] ;
                    callc++;
                }

                intvall.clear();
                strvall.clear();

                intvall = intvall2;
                strvall = strvall2;


                //VM( func, split( split( vdata, "63616c6c20" )[1], "5b" )[0], intvall, strvall, loopj );
            }
            if ( vdata.find( "6a6e7020" ) != string::npos ) {
                string base, c, badata;
                base = split( vdata, "6a6e7020" )[1];
                if ( base.find( "0c20" ) != string::npos ) { c = split( base, "0c20" )[1]; }
                else { c = split( base, "2c20" )[2]; }
                badata = strpri( vdata );
                if ( intifj( badata, intvall, "jnp" ) == 1 ) {
                    VM( func, c, intvall, strvall, loopj );
                }
            }
            if ( vdata.find( "6a6120" ) != string::npos ) {
                /*
                TODO : This is ja.
                */
                string base, c, badata;
                base = split( vdata, "6a6120" )[1];
                if ( base.find( "0c20" ) != string::npos ) { c = split( base, "0c20" )[1]; }
                else { c = split( base, "2c20" )[2]; }
                badata = strpri( vdata );
                if ( intifj( badata, intvall, "ja" ) == 1 ) {
                    VM( func, c, intvall, strvall, loopj );
                }
            }
            if ( vdata.find( "6a616520" ) != string::npos ) {
                /*
                ? This is "jae"
                ? a == b { func[c] }
                ? summary : if ( equal )
                ? base : base string
                */
                string base, a, c;
                base = split( vdata, "6a616520" )[1];
                a = strpri( split( base, "2c20" )[0] );
                b = strpri( split( split( base, "2c20" )[1], "0c20" )[0] );
                if ( base.find( "0c20" ) != string::npos ) { c = split( base, "0c20" )[1]; }
                else { c = split( base, "2c20" )[2]; }
                if ( intkeyfind( intvall, a ) ) {
                    if ( intkeyfind( intvall, b ) ) {
                        if ( atoi( a.c_str() ) == atoi( b.c_str() ) ) {
                            VM( func, c, intvall, strvall, loopj );
                        }
                    }
                    else 
                    if ( atoi( a.c_str() ) == intvall[b] ) {
                        VM( func, c, intvall, strvall, loopj );
                    }
                }                
            }
            if ( vdata.find( "706f7020" ) != string::npos ) {
                // TODO : This is "pop"
                string arg = strpri( split( vdata, "706f7020" )[1]);
                strvall [ arg ] = strvall[ to_string( popc ) ];
                intvall [ arg ] = intvall[ to_string( popc ) ];
                popc++;
            }
            if ( vdata.find( "72657420" ) != string::npos ) {
                // TODO : This is return ( ret )
                string base = split( vdata, "72657420" )[1];
                string funcn, arg;
                if ( vdata.find( "0c20" ) != string::npos ) {
                    funcn = split( base, "c20" )[0];
                    arg = split( base, "c20" )[1];
                }
                else {
                    funcn = split( base, "2c20" )[0];
                    arg = split( base, "2c20" )[1];
                }
                if ( fode == "int" ) {
                    intvall [ strpri( funcn ) ] = atoi( strpri( arg ).c_str() ) ;
                }
                else
                if ( fode == "str" ) {
                    strvall [ strpri( funcn ) ] = strpri( arg.c_str() ) ;
                }// TODO
            }
            if ( vdata.find( "666f64653e" ) != string::npos ) {
                fode = strpri( split( vdata, "3e" )[1] );
            }
        }
    }
}

int main( int argc, char **arg ){
    
    ifstream fin( split( arg[1], "." )[0], ios::in | ios::binary );
    string funcname, data;
    vector<string> vec;
    map<string, string> func;
    map <string, string> strvall;
    map <string, int> intvall;
    int hex, loopj = 0;

    char buf[16];
    while(!fin.eof()) {
        fin.read(buf,sizeof(16));
        string data2( buf, 4 );
        data += data2;
    }
    vec = split( data, "3b" );
    funcname = "6d61696e";
    for ( int i = 0; i < vec.size(); i++ ) {
        vec[i] = vec[i] + "3b";
        if ( vec[i].find("3a") != string::npos ) {
            func[funcname] += split( vec[i], "3a" )[1];
        }
        else 
        if ( vec[i] != "3b" ) {
            func[funcname] += vec[i];
        }
    }
    VM( func, "6d61696e", intvall, strvall, loopj );
    return 0;
}