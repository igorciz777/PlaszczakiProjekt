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
    for (int i = 0; i < p.size(); i++)
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
                for (int j = 0; j < x->wzorce.size(); j++)
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
                for (int j = 0; j < x->wzorce.size(); j++)
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
    for (int i = 0; i < s.size(); i++)
    {
        if (!x->nast[s[i]])
        {
            x->nast[s[i]] = new Wezel();
        }
        x = x->nast[s[i]];
    }
    x->wzorce.push_back(id);
}

Wezel* AhoCorasick::sufiks(Wezel* x, char c)
{
    while (x != trie && !x->nast[c])
    {
        x = x->sufiks;
    }
    if (x->nast[c])
    {
        x = x->nast[c];
    }
    return x;
}

void AhoCorasick::szukaj(std::string s)
{
    Wezel* x = trie;
    for (int i = 0; i < s.size(); i++)
    {
        x = sufiks(x, s[i]);
        for (int j = 0; j < x->wzorce.size(); j++)
        {
            std::cout << "Znaleziono wzorzec " << x->wzorce[j] << " na pozycji " << i << std::endl;
        }
    }
}