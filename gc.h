#ifndef GC_H_INCLUDED
#define GC_H_INCLUDED

#include <cstddef> // for std::nullptr_t
#include <functional> // for std::hash

template <typename T>
class enable_gc_ptr_from_this;

template <typename T>
class gc_pointer
{
    template <typename U>
    friend class enable_gc_ptr_from_this;
private:
    T *ptr;
    struct from_this_t
    {
    };
    constexpr gc_pointer(T *ptr, from_this_t)
        : ptr(ptr)
    {
    }
public:
    constexpr gc_pointer()
        : ptr(nullptr)
    {
    }
    constexpr gc_pointer(std::nullptr_t)
        : gc_pointer()
    {
    }
    template <typename U>
    constexpr gc_pointer(const gc_pointer<U> &ptr)
        : ptr(ptr.get())
    {
    }
    template <typename U>
    gc_pointer(gc_pointer<U> &&ptr)
        : ptr(ptr.get())
    {
        ptr = nullptr;
    }
    template <typename U>
    const gc_pointer &operator =(const gc_pointer<U> &ptr)
    {
        this->ptr = ptr.get();
        return *this;
    }
    template <typename U>
    const gc_pointer &operator =(gc_pointer<U> &&ptr)
    {
        this->ptr = ptr.get();
        ptr = nullptr;
        return *this;
    }
    const gc_pointer &operator =(std::nullptr_t)
    {
        this->ptr = nullptr;
        return *this;
    }
    template <typename U>
    explicit constexpr gc_pointer(U *ptr)
        : ptr(ptr)
    {
    }
    template <typename U, typename D>
    constexpr gc_pointer(U *ptr, const gc_pointer<D> &deleter)
        : ptr(ptr)
    {
    }
    T *get() const
    {
        return ptr;
    }
    T *operator ->() const
    {
        return ptr;
    }
    T &operator *() const
    {
        return *ptr;
    }
    constexpr operator bool() const
    {
        return ptr != nullptr;
    }
    constexpr bool operator !() const
    {
        return ptr == nullptr;
    }
    template <typename U>
    friend constexpr bool operator !=(const gc_pointer<T> &a, const gc_pointer<U> &b)
    {
        return a.get() != b.get();
    }
    friend constexpr bool operator !=(const gc_pointer<T> &a, std::nullptr_t)
    {
        return a.get() != nullptr;
    }
    friend constexpr bool operator !=(std::nullptr_t, const gc_pointer<T> &b)
    {
        return nullptr != b.get();
    }
    template <typename U>
    friend constexpr bool operator ==(const gc_pointer<T> &a, const gc_pointer<U> &b)
    {
        return a.get() == b.get();
    }
    friend constexpr bool operator ==(const gc_pointer<T> &a, std::nullptr_t)
    {
        return a.get() == nullptr;
    }
    friend constexpr bool operator ==(std::nullptr_t, const gc_pointer<T> &b)
    {
        return nullptr == b.get();
    }
    template <typename U>
    friend constexpr bool operator <(const gc_pointer<T> &a, const gc_pointer<U> &b)
    {
        return a.get() < b.get();
    }
    friend constexpr bool operator <(const gc_pointer<T> &a, std::nullptr_t)
    {
        return a.get() < nullptr;
    }
    friend constexpr bool operator <(std::nullptr_t, const gc_pointer<T> &b)
    {
        return nullptr < b.get();
    }
    template <typename U>
    friend constexpr bool operator >(const gc_pointer<T> &a, const gc_pointer<U> &b)
    {
        return a.get() > b.get();
    }
    friend constexpr bool operator >(const gc_pointer<T> &a, std::nullptr_t)
    {
        return a.get() > nullptr;
    }
    friend constexpr bool operator >(std::nullptr_t, const gc_pointer<T> &b)
    {
        return nullptr > b.get();
    }
    template <typename U>
    friend constexpr bool operator <=(const gc_pointer<T> &a, const gc_pointer<U> &b)
    {
        return a.get() <= b.get();
    }
    friend constexpr bool operator <=(const gc_pointer<T> &a, std::nullptr_t)
    {
        return a.get() <= nullptr;
    }
    friend constexpr bool operator <=(std::nullptr_t, const gc_pointer<T> &b)
    {
        return nullptr <= b.get();
    }
    template <typename U>
    friend constexpr bool operator >=(const gc_pointer<T> &a, const gc_pointer<U> &b)
    {
        return a.get() >= b.get();
    }
    friend constexpr bool operator >=(const gc_pointer<T> &a, std::nullptr_t)
    {
        return a.get() >= nullptr;
    }
    friend constexpr bool operator >=(std::nullptr_t, const gc_pointer<T> &b)
    {
        return nullptr >= b.get();
    }
};

template <typename T>
class enable_gc_ptr_from_this
{
protected:
    gc_pointer<T> gc_ptr_from_this()
    {
        return gc_pointer<T>(this, gc_pointer<T>::from_this_t);
    }
    gc_pointer<const T> gc_ptr_from_this() const
    {
        return gc_pointer<const T>(this, gc_pointer<const T>::from_this_t);
    }
};

template <typename T, typename ...Args>
gc_pointer<T> make_gc_ptr(Args &&... args)
{
    return gc_pointer<T>(new T(std::forward<Args>(args)...));
}

template <typename T, typename U>
gc_pointer<T> static_pointer_cast(const gc_pointer<U> &ptr) noexcept
{
    return gc_pointer<T>(static_cast<T *>(ptr.get()));
}

template <typename T, typename U>
gc_pointer<T> const_pointer_cast(const gc_pointer<U> &ptr) noexcept
{
    return gc_pointer<T>(const_cast<T *>(ptr.get()));
}

template <typename T, typename U>
gc_pointer<T> dynamic_pointer_cast(const gc_pointer<U> &ptr) noexcept
{
    return gc_pointer<T>(dynamic_cast<T *>(ptr.get()));
}

namespace std
{
template <typename T>
class hash<gc_pointer<T>>
{
private:
    hash<T *> hasher;
public:
    size_t operator()(const gc_pointer<T> &ptr) const
    {
        return hasher(ptr.get());
    }
};
}

#endif // GC_H_INCLUDED
