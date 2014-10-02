class PropertyContainer;
 
class PropertyProxy
{
public:
    PropertyProxy(PropertyContainer* pContainer, const char* pKey)
    : m_pContainer(pContainer)
    , m_pKey(pKey)
    {}
 
    template<typename ValueType>
    operator ValueType()
    {
        return m_pContainer->GetValueImpl<ValueType>(m_pKey);
    }
 
private:
    PropertyContainer* m_pContainer;
    const char* m_pKey;
}
 
class PropertyContainer
{
public:
    PropertyProxy GetValue(const char* pKey)
    {
        return PropertyProxy(this, pKey);
    }
 
    template<typename ValueType>
    ValueType GetValueImpl(const char* pKey);
    ... ...
}
 
PropertyContainer pc;
bool boolValue = pc.GetValue("FooBoolValue");
char charValue = pc.GetValue("FooCharValue");
int intValue = pc.GetValue("FooIntValue");
float floatValue = pc.GetValue("FooFloatValue");
