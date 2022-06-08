#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#ifndef STRCT
#define STRCT


struct elem{
    int el{0};
    int selec{0};
};
#endif

extern void disp(sf::RenderWindow&, const std::vector<elem>);

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
