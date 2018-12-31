unsigned long long ChartoInt (char* A);

CacheMemory** Creator(int SIndex,int x,int Associativity);

int BitTransformation(int x);

unsigned long long Transformation(unsigned long long x, int y);

void CheckifEmpty(int SIndex,int x,int Associativity);

int DivisionCalc (int x, int y);

int Increment(int x);

void Read(unsigned long long Tagg, int x,unsigned long long Setter,int Associativity);

void Write(unsigned long long Tagg,int x,unsigned long long Setter,int Associativity);

void Fetcher1(unsigned long long Tagg,unsigned long long Setter,int Associativity,int x,unsigned long long TaggA,unsigned long long SetterA);

void Fetcher2(unsigned long long Tagg,unsigned long long Setter,int Associativity,int x,unsigned long long TaggA,unsigned long long SetterA);

void PrintCache(int MemoryRead,int MemoryWrite,int CacheHit,int CacheMiss);

void Reader1(unsigned long long Tagg,int x,unsigned long long Setter,int Associativity);

void Writer1(unsigned long long Tagg,int x,unsigned long long Setter,int Associativity);

void Fetcher3(unsigned long long Tagg,unsigned long long Setter,int Associativity,int x,unsigned long long TaggA,unsigned long long SetterA);

void Fetcher4(unsigned long long Tagg,unsigned long long Setter,int Associativity,int x,unsigned long long TaggA,unsigned long long SetterA);



