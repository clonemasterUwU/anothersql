#ifndef ANOTHERSQL_PAGE_H
#define ANOTHERSQL_PAGE_H

class LockContext;

class BufferManager;

class Page { ;
protected:
    Page(LockContext &lc, BufferManager &bufferManager) : _lockContext(lc), _bufferManager(bufferManager) {}

    std::reference_wrapper<BufferManager> _bufferManager;
    std::reference_wrapper<LockContext> _lockContext;
};


#endif //ANOTHERSQL_PAGE_H
