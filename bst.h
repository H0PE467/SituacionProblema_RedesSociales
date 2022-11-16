#include <iostream>
using namespace std;

template <typename T> class Nodo {
  T data;
  Nodo<T> *left;
  Nodo<T> *right;
  template <typename U> friend class BST;
  template <typename U> friend class AVL;
  /**
   * @brief Constructor de nodo
   * @param data dato a agregar
   * Complejidad: O(1)
   */
  Nodo(T data) {
    this->data = data;     // O(1)
    this->left = nullptr;  // O(1)
    this->right = nullptr; // O(1)
  }
};

template <typename T> class BST {
private:
  Nodo<T> *root;
  int _length;
  /**
   * @brief Inserta un nodo al arbol
   * @param nodo referencia del apuntador del nodo a operar
   * @param dato dato a agregar
   * Complejidad: O(n)
   */
  void insert(Nodo<T> *&nodo, T dato) {
    if (!nodo) // O(1)
    {
      nodo = new Nodo<T>(dato);   // O(1)
      
    } else if (dato < nodo->data) // O(1)
    {
      insert(nodo->left, dato);   // O(n)
    } else if (dato > nodo->data) // O(1)
    {
      insert(nodo->right, dato); // O(n)
    }
  }
  /**
   * @brief imprime el codigo siguiendo la secuencia in orden
   * left
   * out
   * right
   * @param nodo referencia al apuntador del nodo a operar
   * Complejidad: O(n)
   */
  void inOrden(Nodo<T> *&nodo) {
    if (nodo) // O(1)
    {
      inOrden(nodo->left);                  // O(n)
      cout << " | " << nodo->data << " | "; // O(1)
      inOrden(nodo->right);                 // O(n)
    }
  }
  ostream &print(Nodo<T> *&nodo, ostream &out) {
    if (nodo) // O(1)
    {
      print(nodo->left, out);              // O(n)
      out << " | " << nodo->data << " | "; // O(1)
      print(nodo->right, out);             // O(n)
    }
    return out;
  }
  /**
   * @brief imprime el codigo siguiendo la secuencia pre orden
   * out
   * left
   * right
   * @param nodo referencia al apuntador del nodo a operar
   * Complejidad: O(n)
   */
  void preOrden(Nodo<T> *&nodo) {
    if (nodo) {
      cout << " | " << nodo->data << " | "; // O(1)
      preOrden(nodo->left);                 // O(n)
      preOrden(nodo->right);                // O(n)
    }
  }
  /**
   * @brief imprime el codigo siguiendo la secuencia post orden
   * left
   * right
   * out
   * @param nodo referencia al apuntador del nodo a operar
   * Complejidad: O(n)
   */
  void postOrden(Nodo<T> *&nodo) {
    if (nodo) // O(1)
    {
      preOrden(nodo->left);                 // O(n)
      preOrden(nodo->right);                // O(n)
      cout << " | " << nodo->data << " | "; // O(1)
    }
  }
  /**
   * @brief igual al in order, pero al reves
   * right
   * out
   * left
   * @param nodo referencia al apuntador del nodo a operar
   * Complejidad: O(n)
   */
  void inNotOrden(Nodo<T> *&nodo) {
    if (nodo) // O(1)
    {
      inNotOrden(nodo->right);              // O(n)
      cout << " | " << nodo->data << " | "; // O(1)
      inNotOrden(nodo->left);               // O(n)
    }
  }
  /**
   * @brief revisa si el arbol contiene un dato
   * @param nodo referencia al apuntador del nodo a operar
   * @param dato dato a buscar
   * @return 0 si no tiene el elemento, 1 si lo tiene
   * Complejidad: O(n)
   */
  bool contains(Nodo<T> *&nodo, T dato) {
    if (!nodo)             // O(1)
      return false;        // O(1)
    if (dato < nodo->data) // O(1)
    {
      return contains(nodo->left, dato); // O(n)
    } else if (dato > nodo->data)        // O(1)
    {
      return contains(nodo->right, dato); // O(n)
    }
    return true; // O(1)
  }
  /**
   * @brief Regresa el nodo con el mayor valor
   * @param nodo referencia al apuntador del nodo a operar
   * @return el mayor dato
   * Complejidad: O(n)
   */
  T max(Nodo<T> *&nodo) {
    if (!nodo->right)        // O(1)
      return nodo->data;     // O(1)
    return max(nodo->right); // O(n)
  }
  /**
   * @brief Regresa el nodo con el menor valor
   * @param nodo referencia al apuntador del nodo a operar
   * @return el menor dato
   * Complejidad: O(n)
   */
  T min(Nodo<T> *&nodo) {
    if (!nodo->left)        // O(1)
      return nodo->data;    // O(1)
    return min(nodo->left); // O(n)
  }
  /**
   * @brief regresa el numero de nodos del arbol con recursion
   * @param nodo referencia al apuntador del nodo a operar
   * @return el numero de nodos
   * Complejidad: O(n)
   */
  int lengthRec(Nodo<T> *&nodo) {
    if (!nodo)
      return 0;
    int n = 1;
    return 1 + lengthRec(nodo->left) + lengthRec(nodo->right);
  }

  bool remove(Nodo<T> *&nodo, T dato) {
    if (!contains(nodo, dato))
      return 0;
    if (dato < nodo->data) // O(1)
    {
      return remove(nodo->left, dato); // O(n)
    } else if (dato > nodo->data)      // O(1)
    {
      return remove(nodo->right, dato); // O(n)
    } else {
      if (!nodo->right && !nodo->left) {
        nodo = nullptr;
        return true;
        /*Borra nodo y regresa true*/
      }
      /* Obtén el left de nodo.
      Asigna a temp el nodo.
      Asigna a nodo el left
      Borra temp y regresa true*/
      else if (!nodo->right && nodo->left) {
        Nodo<T> *&temp = nodo->left;
        nodo = nodo->left;
        temp = nullptr;
        return true;
      }
      /* Obtén el right de nodo.
      Asigna a temp el nodo.
      Asigna a nodo el right
      Borra temp y regresa true*/
      else if (nodo->right && !nodo->left) {
        Nodo<T> *&temp = nodo->right;
        nodo = nodo->right;
        temp = nullptr;
        return true;
      } else {
        auto temp = nodo->right;
        while (temp->left)
          temp = temp->left;
        nodo->data = temp->data;
        remove(nodo->right, temp->data);
      }
    }
  }
  
  int height(Nodo<T> *&nodo) const {
    if (!nodo)
      return -1;
    int leftHeight = height(nodo->left);
    int rightHeight = height(nodo->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
  }


public:
  /**
   * @brief Constructor del arbol binario
   * Complejidad: O(1)
   */
  BST() {
    root = nullptr; // O(1)
    _length = 0;    // O(1)
  }
  /**
   * @brief insterta un dato
   * @param dato el dato a insertar
   * Complejidad: O(n)
   */
  void insert(T dato) {
    _length++;      // O(1)
    if (is_empty()) // O(1)
    {
      root = new Nodo<T>(dato); // O(1)
    } else {
      insert(root, dato); // O(n)
    }
  }
  /**
   * @brief Revisa si el arbol esta vacio
   * @return 1 si esta vacio, 0 en caso contrario
   * Complejidad: O(1)
   */
  bool is_empty() {
    return !root; // O(1)
  }
  /**
   * @brief Saca los valores con la secuencia in order
   * Complejidad: O(n)
   */
  void inOrden() {
    inOrden(root); // O(n)
  }
  /**
   * @brief Saca los valores con la secuencia pre order
   * Complejidad: O(n)
   */
  void preOrden() {
    preOrden(root); // O(n)
  }
  /**
   * @brief Saca los valores con la secuencia post order
   * Complejidad: O(n)
   */
  void postOrden() {
    postOrden(root); // O(n)
  }
  /**
   * @brief Secuencia in order invertida
   * Complejidad: O(n)
   */
  void inNotOrden() {
    inNotOrden(root); // O(n)
  }
  /**
   * @brief Analiza si el arbol contiene el dato
   * @return 0 si no lo contiene
   * @return 1 si lo contiene
   * Complejidad: O(n)
   */
  bool contains(T dato) { return contains(root, dato); }
  /**
   * @brief da el numero de nodos usando una variable _length
   * @return el numero de nodos
   */
  int length() { return _length; }
  /**
   * @brief Saca el valor maximo del arbol
   * Complejidad: O(n)
   */
  T max() { return max(root); }
  /**
   * @brief Saca el valor minimo del arbol
   * Complejidad: O(n)
   */
  T min() { return min(root); }
  /**
   * @brief Da el numero de nodos de manera recursiva.
   * Complejidad: O(n)
   */
  int lengthRec() { return lengthRec(root); }
  bool remove(T dato) { return remove(root, dato); }

  T getroot() { return root->data; }

  int height() const { return height(root); }

  void balanceo() {
    if (is_empty())
      cout << "Esta vacio\n";
    else {
      int left = height(root->left), right = height(root->right), diff;
      cout << "ALTURA IZQUIERDA: " << left << "\tALTURA DERECHA: " << right
           << "\n";
      diff = left - right;
      diff = (diff < 0) ? -diff : diff;
      if (diff <= 1) {
        cout << "Está balanceado\n";
      } else if (left > right) {
        cout << "La izquierda está más pesada\n";
      } else if (left < right) {
        cout << "La derecha está más pesada\n";
      }
    }
  }

  


  friend ostream &operator<<(ostream &out, BST<T> &bst) {
    return bst.print(bst.root, out);
  }
};


template <typename T> class PriorityQueue : private BST<T> {
public:
  void insert(T dato) { BST<T>::insert(dato); }
  T dequeueMax() {
    T maximum = BST<T>::max();
    BST<T>::remove(maximum);
    return maximum;
  }
  T dequeueMin() {
    T minimum = BST<T>::min();
    BST<T>::remove(minimum);
    return minimum;
  }
  bool is_empty() { return BST<T>::is_empty(); }
  int size() { return BST<T>::length(); }
  void printAsc() { BST<T>::inOrden(); }
  void printDesc() { BST<T>::inNotOrden(); }
};