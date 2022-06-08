#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <windows.h>


inline float fromMsToSec(auto ms)
{
    return (float)ms / 1000;
}


auto start = std::chrono::steady_clock::now();

std::string Smsg, Tmsg, Emsg;
sf::RectangleShape bar;


enum SORTS{
    ZERO,
    BUBBLE,
    INSERTION,
    QUICK,
    MERGE,
    SELECTION,
    HEAP,
    COUNT
};

struct elem{
    int el{0};
    int selec{0};
};

elem make_elem(int x, bool s = 0){
    elem a;
    a.el = x;
    a.selec = s;
    return a;
}

int bblsrt(std::vector<elem>&, sf::RenderWindow&);
int instsrt(std::vector<elem>&, sf::RenderWindow&);
int qsrt(std::vector<elem>&, sf::RenderWindow&, int, int);
int msrt(std::vector<elem>&, sf::RenderWindow&, int , int);


void disp(sf::RenderWindow&, const std::vector<elem>);

int main(){
    bar.setFillColor(sf::Color::White);
    bar.setSize(sf::Vector2f(10, 60));  

    SORTS mod;
    srand(time(0));

    int n, _mod;

    std::cin>>n;
    std::cout<<"Mode? (bbl, inst, qsrt, msrt)"; std::cin>>_mod;

    mod = (SORTS)_mod;
    std::vector<elem> v;
    
    for(int i = 1; i<=n; i++){
        v.push_back(make_elem((rand() % 600)+1, 0));
    }
    // v.push_back(make_emel());
    std::random_shuffle(v.begin(), v.end(), [] (int i){return rand()%i;});

    sf::RenderWindow win(sf::VideoMode(1900, 600), "SORT");
    // win.setFramerateLimit(60);
    
    // std::sort(v.begin(), v.end());   
    int q = 0;
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
                case INSERTION:
                    q = instsrt(v, win);
                    Smsg += "Insertion Sort";
                    break;
                case QUICK:
                    q = qsrt(v, win, 0, v.size()-1);
                    Smsg += "Quick Sort";
                    break;
                case MERGE:
                    q = msrt(v, win, 0, v.size()-1);
                    Smsg += "Merge Sort";
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
    float sec = fromMsToSec(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count());
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
    
    //an over
    win.display();
    
}



///sorts!
int bblsrt(std::vector<elem> &v, sf::RenderWindow& win){
    bool sort = 1;
    while(sort){
        sort = 0;
        for(int i = 0; i<v.size()-1; i++){
            v[i].selec = 1;
            if(v[i].el > v[i+1].el){
                sort = 1;
                std::swap(v[i].el, v[i+1].el);
            }
            disp(win, v);
            v[i].selec = 0;
            // Sleep(1);
        }
    }
    return 1;
}
int instsrt(std::vector<elem>& v, sf::RenderWindow& win){
    int n = v.size();
    for(int i = 0; i<n; i++){
        v[i].selec = 1;
        for(int j = i; j>0; j--){
            v[j].selec = 1;
            if(v[j].el < v[j-1].el){
                std::swap(v[j].el, v[j-1].el);
            }
            disp(win, v);
            v[j].selec = 0;
        }
        v[i].selec = 0;
    }
    return 1;
}
int qsrt(std::vector<elem>& v, sf::RenderWindow& win, int l, int r){
    if(l < r){
        int m = (l+r)/2;
        std::swap(v[l], v[m]);
        int i = l, j = r, d = 0;
        while(i<j){
            v[i].selec = v[j].selec = 1;
            if(v[i].el > v[j].el){
                std::swap(v[i], v[j]);
                d = 1-d;
            }
            disp(win, v);
            v[i].selec = v[j].selec = 0;
            i += d;
            j -= 1-d;
        }
        qsrt(v, win, l, i-1);
        qsrt(v, win, i+1, r);
    }
    disp(win, v);
    return 1;
}
int msrt(std::vector<elem>& v, sf::RenderWindow& win, int l, int r){
    if(l < r){
        int m = (l+r)/2;
        msrt(v, win, l, m);
        msrt(v, win, m+1, r);
        std::vector<int> tmp;
        int i = l, j = m+1;
        while(i < m+1 && j <= r){
            v[i].selec = v[j].selec = 1;
            if(v[i].el > v[j].el) {
                tmp.push_back(v[j].el);
                disp(win, v);
                v[i].selec = v[j].selec = 0;
                j++;
            }
            else {
                tmp.push_back(v[i].el);
                disp(win, v);
                v[i].selec = v[j].selec = 0;
                i++;
            }
        }
        while(i < m+1){
            v[i].selec = 1;
            disp(win, v);
            v[i].selec = 0;
            tmp.push_back(v[i++].el);
        }
        while(j <= r){
            v[j].selec = 1;
            disp(win, v);
            v[j].selec = 0;
            tmp.push_back(v[j++].el);
        }

        if(l != 0 || r != v.size()-1){
            for(int i = 0; i<tmp.size(); i++){
                v[l+i].selec = 1;
                disp(win, v);
                v[l+i].selec = 0;
                v[l+i].el = tmp[i];
            }
        }
        else{
            for(int i = 0; i<tmp.size(); i++){
                v[l+i].selec = 2;
                disp(win, v);
                v[l+i].el = tmp[i];
            }
        }
    }
    return 1;
}

/*


*/