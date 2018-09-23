#ifndef MARIAN_SMARTPOINTER_HPP
#define MARIAN_SMARTPOINTER_HPP

namespace marian {
  /** \ingroup utils
   * \brief Template of deep-coping smart pointer 
   */
  template< class T>
  class SmartPointer {
  public:
    /** \brief Default constructor
     */
    SmartPointer() {
      data_ptr_ = 0;
    }
    
    /** \brief Constructor
     */    
    SmartPointer(const T& inner) {
      data_ptr_ = inner.clone();
    }
    
    /** \brief Destructor
     */  
    ~SmartPointer() {
      if (data_ptr_ != 0)
	delete data_ptr_;
    }
    
    /** \brief Copy constructor
     */  
    SmartPointer(const SmartPointer<T>& original) {
      if (original.data_ptr_ != 0) {
	data_ptr_ = original.data_ptr_->clone();
      } else {
	data_ptr_=0;
      }
    }
    
    /** \brief Assignment operator
     */   
    SmartPointer& operator=(const SmartPointer<T>& original) {
      if (this != &original) {
	if (data_ptr_ != 0) {
	  delete data_ptr_;
	}
	data_ptr_ = (original.data_ptr_ != 0) ? original.data_ptr_->clone() : 0;
      }
      return *this;
    }
     
    /** \brief Method dereferencing pointer
     */   
    T& operator*() {
      return *data_ptr_; 
    }

    /** \brief Method dereferencing pointer
     */   
    const T& operator*() const {
      return *data_ptr_; 
    }

    /** \brief Method dereferencing pointer
     */   
    T* operator->() {
      return data_ptr_;
    }

    /** \brief Method dereferencing pointer
     */   
    const T* operator->() const {
      return data_ptr_;
    }

    /** \brief Check if pointer owns any object
     */   
    bool isEmpty() const {
      if (data_ptr_) {
	return false;
      }
      return true;
    }
    
  private:
    T* data_ptr_; /*!< \brief Pointer to data owned by pointer*/  
  };
}  // namespace marian
#endif
