#include "CMap.h"

CMap notFound;

bool orderCMapByCount(pair<CTYPE> first, pair<CTYPE> second)
{
    return first.second.GetWord().GetCount() > second.second.GetWord().GetCount();
}


CMap::CMap()
{
    //_markovLength = 3;
}


CMap& CMap::insert(  const string& str  )
{

    pair<CIterator,bool> ret = _map.insert( CPair(str, CMap()) );

    // The pair::second element in the pair is set to true if a new element
    // was inserted or false if an equivalent key already existed.
    if( ret.second == false) //EXIST
    {
        ret.first->second.incrementWordCount();
        //cout << "Element already exist --- ";
        //cout << str << " :          " << ret.first->second.GetWord().GetCount() << endl;
    }
    else //EXIST PAS
    {
        ret.first->second.SetWord( str );
    }

    return ret.first->second;
}

CAttribute* CMap::GetWordAttribute(const string& att)
{
	return (*GetWordPtr())[att];
}

bool CMap::AddWordAttribute(const string& att_name, CAttribute* att)
{
	return GetWordPtr()->AddAttribute(att_name, att);
}

CMap CMap::GetWordMap( const string& str ) const
/// @todo What happen when the word "str" is not in the map.
{
    if (_map.find(str) != _map.end())
        return _map.find( str )->second;

    return notFound;
}

CWord CMap::GetWord() const
{
    return _word;
}


void CMap::SetWord( const string& word )
{
    _word.SetWord( word );
}


void CMap::SetWordCount(const int &count)
{
    _word.SetCount(count);
}


void CMap::incrementWordCount()
{
    _word.increment();
}


void CMap::Print(ostream& stream)
{
    for( CIterator i = _map.begin(); i != _map.end(); ++i )
    {
		stream << setw(15) << left << setfill(' ') << i->second.GetWord().GetString() << "("
			   << i->second.GetWord().GetCount() << ") ";
        stream << "size : " << i->second.GetSize() << endl;
    }
}

unsigned long CMap::GetSize() const
{
    return _map.size();
}


void CMap::SetMap(map<CTYPE>& m)
{
	if (_map.size() != 0)
	{
		cout << "Map wasn't empty." << endl;
	}
	_map = m;
}

// Operators
bool operator== (const CMap &map1, const CMap &map2)
{
    return (map1._map == map2._map) && (map1._word == map2._word);
}

