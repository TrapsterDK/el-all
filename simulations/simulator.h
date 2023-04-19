#include <stdio.h>

#define GET_BIT(x, n) ((x >> n) & 1)
#define SET_BIT(x, n) (x |= (1 << n))
#define CLEAR_BIT(x, n) (x &= ~(1 << n))

#define INPUT 1
#define OUTPUT 0

void Error(char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("Error: ");
    vprintf(format, args);
    va_end(args);
}

void Error_Exit(char *format, ...)
{
    va_list args;
    va_start(args, format);
    printf("Fatal: ");
    vprintf(format, args);
    va_end(args);
    exit(1);
}

struct Connection
{
    struct Controller *controller1;
    struct Controller *controller2;
    long long int used_pins;
};
typedef struct Connection Connection;

struct Connections
{
    struct Connection *connections;
    int size;
};
typedef struct Connections Connections;

Connection *Create_Connection(Controller *controller1, Controller *controller2)
{
    Connection *connection = malloc(sizeof(Connection));
    connection->controller1 = controller1;
    connection->controller2 = controller2;
    return connection;
}

Connections *Create_Connections()
{
    Connections *connections = malloc(sizeof(Connections));
    connections->connections = malloc(sizeof(Connection));
    connections->size = 0;
    return connections;
}

void Delete_Connections(Connections *connections)
{
    free(connections->connections);
    free(connections);
}

void Update_Connections(Connections *connections)
{
    for (int i = 0; i < connections->size; i++)
    {
        Connection *connection = &connections->connections[i];

        // check 2 controllers are not trying to both be inputs
        int both_inputs = connection->controller1->pins_direction & connection->controller2->pins_direction;
        if (both_inputs)
        {
            Error_Exit("Controller %s and %s have conflicting pins", connection->controller1->name, connection->controller2->name);
        }

        for (int j = 0; j < 64; j++)
        {
            if (!GET_BIT(connection->used_pins, j))
            {
                continue;
            }

            int direction = GET_BIT(connection->controller1->pins_direction, j) ? INPUT : OUTPUT;
            Controller *from = direction == INPUT ? connection->controller1 : connection->controller2;
            Controller *to = direction == INPUT ? connection->controller2 : connection->controller1;

            if (GET_BIT(to->changed_this_cycle, j))
            {
                Error_Exit("Connection %s.%d is being updated twice in the same cycle", to->name, j);
            }

            int value = Get_Pin(from, j);
            Set_Pin(to, j, value);

            SET_BIT(to->changed_this_cycle, j);
        }
    }

    for (int i = 0; i < connections->size; i++)
    {
        Connection *connection = &connections->connections[i];
        connection->controller1->changed_this_cycle = 0;
        connection->controller2->changed_this_cycle = 0;
    }
}

void Add_Connection(Connections *connections, Connection *connection)
{
    connections->connections = realloc(connections->connections, sizeof(Connection) * (connections->size + 1));
    connections->connections[connections->size] = *connection;
    connections->size++;
}

struct Controller
{
    char *name;
    void (*Update)(struct Controller *controller);
    long long int pins;
    long long int pins_direction;
    long long int changed_this_cycle;
};

typedef struct Controller Controller;

Controller *Create_Controller(char *name, void (*Update)(Controller *controller))
{
    Controller *controller = malloc(sizeof(Controller));
    controller->name = name;
    controller->Update = Update;
    controller->pins_direction = 0;
    controller->changed_this_cycle = 0;
    controller->pins = 0;
    return controller;
}

void Delete_Controller(Controller *controller)
{
    free(controller);
}

void Set_Pin_Direction(Controller *controller, int pin, int direction)
{
    if (direction)
    {
        SET_BIT(controller->pins_direction, pin);
    }
    else
    {
        CLEAR_BIT(controller->pins_direction, pin);
    }
}

void Set_Pin(Controller *controller, int pin, int value)
{
    if (value)
    {
        SET_BIT(controller->pins, pin);
    }
    else
    {
        CLEAR_BIT(controller->pins, pin);
    }
}

int Get_Pin(Controller *controller, int pin)
{
    return GET_BIT(controller->pins, pin);
}

void Update_Controllers(Controller **controllers, int size)
{
    for (int i = 0; i < size; i++)
    {
        controllers[i]->Update(controllers[i]);
    }
}

void Update_Simulator(Controller **controllers, int size, Connections *connections)
{
    Update_Controllers(controllers, size);
    Update_Connections(connections);
}
