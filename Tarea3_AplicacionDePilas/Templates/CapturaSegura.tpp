using std::cout;
using std::cin;
using std::endl;

template <typename N, typename T>
T CapturaSegura<N, T>::TextoSeguro()
{
    T text;
    cin >> text;

    while(cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(), '\n');
        cout << "Ingresa una respuesta v\240lida.\n - ";
        cin >> text;
    }

    return text;
}

template <typename N, typename T>
T CapturaSegura<N, T>::TextoMinimo(unsigned min)
{
    T text;
    cin >> text;

    while(cin.fail() | text.size() < min)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(), '\n');
        cout << "El texto ingresado debe tener m\241nimo " << min << " caracteres.\n - ";
        cin >> text;
    }

    return text;
}

template <typename N, typename T>
T CapturaSegura<N, T>::TextoMaximo(unsigned max)
{
    T text;
    cin >> text;

    while(cin.fail() | text.size() > max)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(), '\n');
        cout << "El texto ingresado debe tener m\240ximo " << max << " caracteres.\n - ";
        cin >> text;
    }

    return text;
}

template <typename N, typename T>
T CapturaSegura<N, T>::TextoCerrado(unsigned min, unsigned max)
{
    T text;
    cin >> text;

    while(cin.fail() || text.size() < min || text.size() > max)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(), '\n');
        
        if(text.size() < min)
        {
            cout << "El texto ingresado debe tener m\241nimo " << min << " caracteres.\n - ";
        }
        else if(text.size() > max)
        {
            cout << "El texto ingresado debe tener m\240ximo " << max << " caracteres.\n - ";
        }
        
        cin >> text;
    }

    return text;
}

template <typename N, typename T>
T CapturaSegura<N, T>::TextoPermitido(const char caracteres[], unsigned int longitudCaracteres) 
{
    T text;
    cin >> text;
    
    while (true) 
    {
        bool valid = true;

        for (char c : text) 
        {
            if (!(std::find(caracteres, caracteres + longitudCaracteres, c) != caracteres + longitudCaracteres)) 
            {
                cout << "\nError: El car\240cter '" << c << "' no est\240 permitido." << endl;
                valid = false;
            }
        }

        if(!valid)
        {
            cout << "\nIngresa de nuevo tu respuesta\n - ";
            cin >> text;
        }
        else
        {
            break;
        }
    }

    return text;
}

template <typename N, typename T>
N CapturaSegura<N, T>::LongitudSegura()
{
    N num;
    cin >> num;

    while(cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(), '\n');
        cout << "Ingresa una respuesta v\240lida.\n - ";
        cin >> num;
    }

    return num;
}

template <typename N, typename T>
N CapturaSegura<N, T>::LongitudPositiva()
{
    N num;
    cin >> num;

    while(cin.fail() || num < 1)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(), '\n');
        
        if(num < 1)
        {
            cout << "\nLa respuesta debe ser mayor a 0.";
            cout << "\nIngresa de nuevo tu respuesta.\n - ";
        }
        
        cin >> num;
    }

    return num;
}

template <typename N, typename T>
N CapturaSegura<N, T>::LongitudMinima(N min)
{
    N num;
    cin >> num;

    while(cin.fail() || num < min)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(), '\n');
        
        if(num < min)
        {
            cout << "\nLa respuesta no puede ser menor a " << min << ".";
            cout << "\nIngresa de nuevo tu respuesta.\n - ";
        }
        
        cin >> num;
    }

    return num;
}

template <typename N, typename T>
N CapturaSegura<N, T>::LongitudMaxima(N max)
{
    N num;
    cin >> num;

    while(cin.fail() || num > max)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(), '\n');
        
        if(num > max)
        {
            cout << "\nLa respuesta no puede ser mayor a " << max << ".";
            cout << "\nIngresa de nuevo tu respuesta.\n - ";
        }
        
        cin >> num;
    }

    return num;
}

template <typename N, typename T>
N CapturaSegura<N, T>::LongitudCerrada(N min, N max)
{
    int num;
    cin >> num;

    while(cin.fail() || num < min || num > max)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(), '\n');
        
        if(num < min)
        {
            cout << "\nLa respuesta no puede ser menor a " << min << ".";
        }
        else if(num > max)
        {
            cout << "\nLa respuesta no puede ser mayor a " << max << ".";
        }
        
        cout << "\nIngresa de nuevo tu respuesta.\n - ";
        cin >> num;
    }

    return num;
}
