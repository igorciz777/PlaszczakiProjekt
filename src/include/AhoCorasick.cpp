/**
 * @file AhoCorasick.cpp
 * @brief Plik źródłowy klasy AhoCorasick
 * 
 * Plik zawiera implementację metod klasy AhoCorasick
 * 
 * @see AhoCorasick.h
 */
#include "AhoCorasick.h"

Wezel::Wezel()
{
    sufiks = 0;
    for (int i = 0; i < 256; i++)
    {
        nast[i] = 0;
    }
}

int AhoCorasick::nast_id = 0;

AhoCorasick::AhoCorasick(std::vector<std::string> &p)
{
    trie = new Wezel();
    for (llu i = 0; i < p.size(); i++)
    {
        wstaw(trie, p[i], i);
    }
    std::queue<Wezel*> q;
    for (int i = 0; i < 256; i++)
    {
        if (trie->nast[i])
        {
            trie->nast[i]->sufiks = trie;
            q.push(trie->nast[i]);
        }
    }
    while (!q.empty())
    {
        Wezel* r = q.front();
        q.pop();
        for (int i = 0; i < 256; i++)
        {
            if (r->nast[i])
            {
                Wezel* x = r->sufiks;
                while (x != trie && !x->nast[i])
                {
                    x = x->sufiks;
                }
                if (x->nast[i])
                {
                    x = x->nast[i];
                }
                r->nast[i]->sufiks = x;
                for (llu j = 0; j < x->wzorce.size(); j++)
                {
                    r->nast[i]->wzorce.push_back(x->wzorce[j]);
                }
                q.push(r->nast[i]);
            }
        }
    }
}

AhoCorasick::AhoCorasick(std::string p){
    trie = new Wezel();
    wstaw(trie, p, 0);
    std::queue<Wezel*> q;
    for (int i = 0; i < 256; i++)
    {
        if (trie->nast[i])
        {
            trie->nast[i]->sufiks = trie;
            q.push(trie->nast[i]);
        }
    }
    while (!q.empty())
    {
        Wezel* r = q.front();
        q.pop();
        for (int i = 0; i < 256; i++)
        {
            if (r->nast[i])
            {
                Wezel* x = r->sufiks;
                while (x != trie && !x->nast[i])
                {
                    x = x->sufiks;
                }
                if (x->nast[i])
                {
                    x = x->nast[i];
                }
                r->nast[i]->sufiks = x;
                for (llu j = 0; j < x->wzorce.size(); j++)
                {
                    r->nast[i]->wzorce.push_back(x->wzorce[j]);
                }
                q.push(r->nast[i]);
            }
        }
    }
}

void AhoCorasick::wstaw(Wezel* x, std::string s, int id)
{
    for (llu i = 0; i < s.size(); i++)
    {
        if (!x->nast[(unsigned char)s[i]])
        {
            x->nast[(unsigned char)s[i]] = new Wezel();
        }
        x = x->nast[(unsigned char)s[i]];
    }
    x->wzorce.push_back(id);
}

Wezel* AhoCorasick::sufiks(Wezel* x, char c)
{
    while (x != trie && !x->nast[(unsigned char)c])
    {
        x = x->sufiks;
    }
    if (x->nast[(unsigned char)c])
    {
        x = x->nast[(unsigned char)c];
    }
    return x;
}

std::vector<std::pair<lli,lli> > AhoCorasick::szukaj(std::string s)
{
    Wezel* x = trie;
    std::vector<std::pair<lli,lli> > wynik;
    for (llu i = 0; i < s.size(); i++)
    {
        x = sufiks(x, s[i]);
        for (llu j = 0; j < x->wzorce.size(); j++)
        {
            wynik.push_back({i, x->wzorce[j]});
        }
    }
    return wynik;
}