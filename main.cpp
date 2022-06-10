#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <windows.h>
#include "sorts.cpp"


inline float fromMsToSec(auto ms)
{
    return (float)ms / 1000;
}


auto start = std::chrono::steady_clock::now();

std::string Smsg, Tmsg, Emsg;
sf::RectangleShape bar;
sf::Font fnt;
sf::Text txt;
float sec = 0;


enum SORTS{
    ZERO,
    BUBBLE,
    SELECTION,
    QUICK,
    MERGE,
    RADIX,
    INSERTION,
    HEAP,
    COUNT
};

#ifndef STRCT
#define STRCT


struct elem{
    int el{0};
    int selec{0};
};
#endif

elem make_elem(int x, bool s = 0){
    elem a;
    a.el = x;
    a.selec = s;
    return a;
}

extern int bblsrt(std::vector<elem>&, sf::RenderWindow&);
extern int ssrt(std::vector<elem>&, sf::RenderWindow&);
extern int qsrt(std::vector<elem>&, sf::RenderWindow&, int, int);
extern int msrt(std::vector<elem>&, sf::RenderWindow&, int , int);
extern int rsrt(std::vector<elem>&, sf::RenderWindow&);


void disp(sf::RenderWindow&, const std::vector<elem>);
int q = 0;
int main(){
    fnt.loadFromFile("ayar.ttf");
    txt.setFont(fnt);
    txt.setCharacterSize(20);

    bar.setFillColor(sf::Color::White);
    bar.setSize(sf::Vector2f(10, 60));  

    SORTS mod;
    srand(time(0));

    int n, _mod;

    std::cin>>n;
    std::cout<<"Mode? (bbl(1), selec(2), qsrt(3), msrt(4), radix(5))"; std::cin>>_mod;

    mod = (SORTS)_mod;
    std::vector<elem> v;
    
    for(int i = 1; i<=n; i++){
        v.push_back(make_elem(i*600/n, 0));
    }
    // v.push_back(make_emel());
    std::random_shuffle(v.begin(), v.end(), [] (int i){return rand()%i;});

    sf::RenderWindow win(sf::VideoMode(1900, 600), "SORT");
    // win.setFramerateLimit(60);
    
    // std::sort(v.begin(), v.end());   
    Smsg = "Sort: ";
    Tmsg = "Visual Time: ";
    Emsg = "Elements: " + std::to_string(n);

    while(win.isOpen()){
        sf::Event event;
        while(win.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                win.close();
        }
        if(!q){
            start = std::chrono::steady_clock::now();
            switch(mod){
                case BUBBLE:
                    q = bblsrt(v, win);
                    Smsg += "Bubble Sort";
                    break;
                case QUICK:
                    q = qsrt(v, win, 0, v.size()-1);
                    Smsg += "Quick Sort";
                    break;
                case MERGE:
                    q = msrt(v, win, 0, v.size()-1);
                    Smsg += "Merge Sort";
                    break;
                case SELECTION:
                    q = ssrt(v, win);
                    Smsg += "Selection Sort";
                    break;
                case RADIX:
                    q = rsrt(v, win);
                    Smsg += "Radix Sort";
                    break;
            }
            for(int i = 0; i<v.size(); i++){
                v[i].selec = 2;
                disp(win, v);
            }
        }
    }
    // for(auto[nr, a]:v){
    //     std::cout<<nr<<' ';
    // }
}

void disp(sf::RenderWindow &win, const std::vector<elem> v){
    //time part
    if(!q)
    sec = fromMsToSec(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count());
    Tmsg = "Visual Time: " + std::to_string(sec);
    Tmsg += "s";
    
    //handle closing the windows
    sf::Event ev;
    if(win.isOpen() == 0) exit(0);
    if(win.pollEvent(ev) && ev.type == sf::Event::Closed){
        win.close();
        return;
    }


    int n = v.size(); //sorry, it had to be done :(
    
    //set the bar
    bar.setPosition(0, 0);
    win.clear();

    //itterate thru the vector
    for(int i = 0; i<=n; i++){

        //set the colors :D
        if(v[i].selec == 1) bar.setFillColor(sf::Color::Red);
        else if(v[i].selec == 0)bar.setFillColor(sf::Color::White);
        else bar.setFillColor(sf::Color::Green);

        //size
        bar.setSize(sf::Vector2f((float)win.getSize().x/n, v[i].el));
        
        //position
        bar.setPosition(bar.getPosition().x+bar.getSize().x, win.getSize().y-v[i].el);

        //and draw it
        win.draw(bar);
        
    }

    //draw the text
    txt.setString(Smsg);
    txt.setPosition(0, 0);
    win.draw(txt);

    txt.setString(Tmsg);
    txt.setPosition(0, 20);
    win.draw(txt);

    txt.setString(Emsg);
    txt.setPosition(0, 40);
    win.draw(txt);

    //an over
    win.display();
    
}



///sorts!


/*


*/