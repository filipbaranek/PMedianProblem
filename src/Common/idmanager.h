#ifndef IDMANAGER_H
#define IDMANAGER_H

class IdManager
{
public:
    static IdManager& instance()
    {
        static IdManager idManager;
        return idManager;
    }

    int nextNodeId()
    {
        return ++_nodeId;
    }

    int nextEdgeId()
    {
        return ++_edgeId;
    }

    int currentNodeId()
    {
        return _nodeId;
    }

    int currentEdgeId()
    {
        return _edgeId;
    }

    void updateNodeId(int id)
    {
        _nodeId = id;
    }

    void updateEdgeId(int id)
    {
        _edgeId = id;
    }

    void restart()
    {
        _nodeId = 0;
        _edgeId = 0;
    }

private:
    IdManager()
        : _nodeId{},
          _edgeId{}
    { }

    ~IdManager() = default;

private:
    int _nodeId;
    int _edgeId;
};

#endif // IDMANAGER_H
