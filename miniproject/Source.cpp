#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<math.h>
#define STRINGLOCX 100.0
#define STRINGLOCY 100.0

// Function prototype section.
int items, side = 30, ndel, diff, k, h = 5, count1 = 0, i = 0, d = 0, del = 0, m, full = 0,sub1,sub2;
float m1[20], m2[20], m3[20];
void drawString1(void* font, float x, float y, char* str);
void displayssl();
void drawstring(float x, float y, char* string, int col, int drawstringflag);
void sll(int value);
void queue(int value);
void draw();
void delt();
void display1();
void title();
void myinit();
void queuewin();

// NODE structure for linked list.
struct node
{
    int info;
    struct node* link;
};

// Structure to store values for display on visualizer.
struct arr
{
    int p;
    int q;
}ar[20];

// Global Variable section.
typedef struct node* NODE;
static NODE first = NULL; // First node of Linked List.
static int count = 0, flag = 1;
int succ = 1, succ1 = 1, ins_succ = 1;
int choice, item, key;
float color[4][3] = { {1.0, 1.0, 1.0}, {0.8, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.8} };
int drawstringflag = 0, printflag = 1, titleflag = 1;

// Allocate memory for node.
NODE getnode()
{
    NODE x;
    x = (NODE)malloc(sizeof(struct node));
    if (x == NULL)
    {
        printf("Insufficient memory!!\n");
        exit(0);
    }
    return x;
}

// Display Linked List.
void lldisplay()
{
    NODE temp;
    int k;
    if (first == NULL)
    {
        printf("The list is empty!\n");
        return;
    }
    printf("\nContents of Singly Linked List: \n");
    temp = first;
    while (temp != NULL)
    {
        for (k = 0; k < count; k++)
        {
            printf("%d", temp->info);
            temp = temp->link;
            printf("\n");
        }
    }
    printf("\n");
}

// Insert element from Front of Linked list.
NODE  insert_front(int item, NODE first)
{
    NODE temp;
    temp = getnode();
    temp->info = item;
    temp->link = first;
    return temp;
}

// Insert element from Rear of Linked list.
NODE insert_rear(int item, NODE first)
{
    NODE temp;
    NODE cur;
    temp = getnode();
    temp->info = item;
    temp->link = NULL;
    if (first == NULL)
        return temp;
    cur = first;
    while (cur->link != NULL)
        cur = cur->link;
    cur->link = temp;
    return first;
}

// Insert node at a specified position.
NODE insert_specified(int item, NODE first)
{
    NODE next, cur, temp;
    temp = getnode();
    temp->info = item;
    if (first == NULL)
    {
        printf("The list is empty! Inserting node at the front...\n");
        temp->link = NULL;
        first = temp;
        return first;
    }
    printf("Enter the key : "); // Key = Node value after which the new node is to be inserted.
    scanf_s("%d", &key);
    cur = first;
    while (cur != NULL)
    {
        next = cur->link;
        if (cur->info == key)
        {
            printf("Key found!\n");
            cur->link = temp;
            temp->link = next;
            return first;
        }
        cur = cur->link;
    }
    if (cur == NULL)
    {
        printf("Search unsuccessful!\n");
        count--;
        ins_succ = 0;
    }
    return first;
}

// Delete node from Front of Linked List.
NODE delete_front(NODE first)
{
    NODE temp;
    if (first == NULL)
    {
        printf("The list is empty, cannot delete!\n");
        count++;
        succ = 0;
        return first;
    }
    temp = first;
    temp = temp->link;
    printf("Deleted item  =  %d \n", first->info);
    free(first);
    return temp;
}

// Delete node from Rear of Linked List.
NODE delete_rear(NODE first)
{
    NODE cur, prev;
    if (first == NULL)
    {
        printf("The list is empty, cannot delete!\n");
        count++;
        succ = 0;
        return first;
    }
    if (first->link == NULL)
    {
        printf("Item to be deleted is %d \n", first->info);
        free(first);
        return NULL;
    }
    prev = NULL;
    cur = first;
    while (cur->link != NULL)
    {
        prev = cur;
        cur = cur->link;
    }
    printf("Deleted item  =  %d \n", cur->info);
    free(cur);
    prev->link = NULL;
    return first;
}

// Delete a specified node from Linked List.
NODE delete_specified(NODE first)
{
    NODE prev, cur;
    if (first == NULL)
    {
        printf("The list is empty, cannot delete!\n");
        count++;
        succ = 0;
        return NULL;
    }
    printf("Enter the key: ");
    scanf_s("%d", &key);
    if (key == first->info)
    {
        cur = first;
        first = first->link;
        free(cur);
        return first;
    }
    prev = NULL;
    cur = first;
    while (cur != NULL)
    {
        if (key == cur->info)
            break;
        prev = cur;
        cur = cur->link;
    }
    if (cur == NULL)
    {
        printf("Search is unsuccessful!\n");
        count++;
        succ1 = 0;
        succ = 0;
        return first;
    }
    prev->link = cur->link;
    free(cur);
    return first;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,480.0);
    title();
}

// Option menu for Linked List operations.
void sll_menu(int choice)
{
    switch (choice)
    {
    case 1:
        printf("Enter the item to be inserted: ");
        scanf_s("%d", &item);
        first = insert_front(item, first);
        count++;
        lldisplay();
        displayssl();
        drawstring(200.0, 130.0, (char*)"NEW NODE INSERTED", 2, 0);
        break;
    case 2:
        printf("Enter the item to be inserted: ");
        scanf_s("%d", &item);
        first = insert_rear(item, first);
        count++;
        lldisplay();
        displayssl();
        drawstring(200.0, 130.0, (char*)"NEW NODE INSERTED", 2, 0);
        break;
    case 3:
        printf("Enter the item to be inserted: ");
        scanf_s("%d", &item);
        ins_succ = 1;
        first = insert_specified(item, first);
        count++;
        lldisplay();
        displayssl();
        if (!ins_succ)
            drawstring(200.0, 130.0, (char*)"KEY NODE DOESN'T EXIST", 2, 0);
        else
            drawstring(200.0, 130.0, (char*)"NEW NODE INSERTED", 2, 0);
        break;
    case 4:
        succ = 1;
        first = delete_front(first);
        count--;
        lldisplay();
        displayssl();
        if (succ)
            drawstring(200.0, 130.0, (char*)"NODE DELETED", 2, 0);
        break;
    case 5:
        succ = 1;
        first = delete_rear(first);
        count--;
        lldisplay();
        displayssl();
        if (succ)
            drawstring(200.0, 130.0, (char*)"NODE DELETED", 2, 0);
        break;
    case 6:
        succ = succ1 = 1;
        first = delete_specified(first);
        count--;
        lldisplay();
        displayssl();
        if (succ)
            drawstring(200.0, 130.0, (char*)"NODE DELETED", 2, 0);
        if (!succ1)
            drawstring(200.0, 130.0, (char*)"KEY NODE DOESN'T EXIST", 2, 0);
        break;
    case 7:
        exit(0);
    }
}

// Initialize window properties. 
void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glMatrixMode(GL_MODELVIEW);
}

// Function to print strings on rendered window.
void drawstring(float x, float y, char* string, int col, int drawstringflag)
{
    char* c;
    glColor3fv(color[col]);
    glRasterPos2f(x, y);
    if (drawstringflag == 0)
    {
        for (c = string; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    else if (drawstringflag == 1)
    {
        for (c = string; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
    else
    {
        for (c = string; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

// Delay function.
void delay()
{
    int i, j;
    for (i = 0; i < 5000; i++)
        for (j = 0; j < 5000; j++)
            ;
}

// Title display function.
void title()
{
    glClearColor(192.0, 192.0, 192.0, 1.0);
    drawstring(170.0, 240.0, (char*)"Singly Linked List Visualizer", 1, 2);
    drawstring(170.0, 300.0, (char*)"Queue Visualizer", 1, 2);
    drawstring(15.0, 70.0, (char*)"Click Mouse Button for operations menu", 3, 0);
    glFlush();
}

// Display function for visualizer.
void displayssl()
{
    int i = 0, j = 0, k = 0, b[20];
    NODE temp;
    glClearColor(192.0, 192.0, 192.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.6);
    drawstring(200.0, 450.0, (char*)"SINGLY LINKED LIST", 1, 0);
    if (first == NULL)
    {
        if (printflag)
        {
            printf("\nEmpty List\n");
            printflag = 0;
        }
    }
    temp = first;
    while (temp != NULL)
    {
        for (k = 0; k < count; k++)
        {
            GLfloat x1 = 50, y1 = 200, x2 = 80, y2 = 225;
            GLfloat x3 = 110, y3 = 250, x4 = 95, y4 = 225;
            GLfloat x5 = 160, y5 = 210, y6 = 240, x6 = 180;
            int pos = 130; // Constant multiplier for positioning.
            if (first->link == NULL)
            {
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_LINES); // Slash to indicate termination of Linked list.
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
            }
            if (temp->link == NULL)
            {
                glColor3f(0.8, 0.2, 0.70);
                glBegin(GL_POLYGON); // Info box.
                glVertex2i(x1 + k * pos, y1);
                glVertex2i(x1 + k * pos, y3);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x2 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON); // Next link box.
                glVertex2i(x2 + k * pos, y1);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_LINES); // Slash to indicate termination of Linked list.s
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
            }
            else
            {
                glColor3f(0.0f, 0.0f, 0.0f);
                glBegin(GL_LINES); // Line pointing to next node.
                glVertex2i(x4 + k * pos, y4);
                glVertex2i(x6 + k * pos, y4);
                glEnd();
                glColor3f(0.0f, 0.0f, 0.0f);
                glBegin(GL_LINES); // Arrow marks.
                glVertex2i(x5 + k * pos, y6);
                glVertex2i(x6 + k * pos, y4);
                glVertex2i(x6 + k * pos, y4);
                glVertex2i(x5 + k * pos, y5);
                glEnd();
                glColor3f(0.8, 0.20, 0.70);
                glBegin(GL_POLYGON); // Info box.
                glVertex2i(x1 + k * pos, y1);
                glVertex2i(x1 + k * pos, y3);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x2 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON); // Next link box.
                glVertex2i(x2 + k * pos, y1);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
            }
            b[j] = temp->info;
            temp = temp->link;
            ar[i].p = b[j] / 10;
            ar[i].q = b[j] % 10;
            ar[i].p = ar[i].p + 48;
            ar[i].q = ar[i].q + 48;
            glColor3f(1.0, 1.0, 0.0);
            glRasterPos2f(55.0 + k * pos, 215.0);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ar[i].p); // Print Node value.
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ar[i].q);
            drawstring(40.0 + k * pos, 185, (char*)"DATA", 1, 1);
            drawstring(85.0 + k * pos, 185, (char*)"LINK", 1, 1);
            i++;
            j++;
            glFlush();
        }
    }
}

int main(int argc, char** argv)
{
    printf("                     MINI PROJECT                       \n\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Menu Window");
    glutDisplayFunc(display);
    init();
    myinit();
    
    for (m = 0; m < 20; m++)
    {
        m1[m] = (float)(rand() % 9) / (m + 7);
        m2[m] = (float)(rand() % 9) / (m + 7);
        m3[m] = (float)(rand() % 9) / (m + 7);
    }
    int sub1 = glutCreateMenu(sll);
    glutAddMenuEntry("Insert Front", 1);
    glutAddMenuEntry("Insert Rear", 2);
    glutAddMenuEntry("Insert Specified", 3);
    glutAddMenuEntry("Delete Front", 4);
    glutAddMenuEntry("Delete Rear", 5);
    glutAddMenuEntry("Delete Specified", 6);
    glutAddMenuEntry("Exit", 7);
    glutCreateMenu(sll);
    glutAddSubMenu("Single Linked List", sub1);
    glutAttachMenu(GLUT_LEFT_BUTTON);

    int sub2 = glutCreateMenu(queue);
    glutAddMenuEntry("Push", 1);
    glutAddMenuEntry("Pop", 2);
    glutAddMenuEntry("Abort", 3);
    glutCreateMenu(queue);
    glutAddSubMenu("Queue", sub2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
void sll(int value) {
    glutCreateWindow("Singly Linked List Visualizer");
    glutDisplayFunc(displayssl);
    init();
    int sub1 = glutCreateMenu(sll);
    glutAddMenuEntry("Insert Front", 1);
    glutAddMenuEntry("Insert Rear", 2);
    glutAddMenuEntry("Insert Specified", 3);
    glutAddMenuEntry("Delete Front", 4);
    glutAddMenuEntry("Delete Rear", 5);
    glutAddMenuEntry("Delete Specified", 6);
    glutAddMenuEntry("Exit", 7);

    glutCreateMenu(sll);
    glutAddSubMenu("Single Linked List", sub1);
    glutAttachMenu(GLUT_LEFT_BUTTON);
    switch (value) {
    case 1:sll_menu(1);
        break;
    case 2:sll_menu(2);
        break;
    case 3:sll_menu(3);
        break;
    case 4:sll_menu(4);
        break;
    case 5:sll_menu(5);
        break;
    case 6:sll_menu(6);
        break;
    case 7:exit(0);
    }
    glutPostRedisplay();
}
void queue(int value) {
    glutDisplayFunc(display1);
    myinit();
    int sub2 = glutCreateMenu(queue);
    glutAddMenuEntry("Push", 1);
    glutAddMenuEntry("Pop", 2);
    glutAddMenuEntry("Abort", 3);

    glutCreateMenu(queue);
    glutAddSubMenu("Queue", sub2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    switch (value) {
        case 1:d++;
            draw();
            break;
        case 2:
            delt();
            break;
        case 3:exit(0);
    }
    glutPostRedisplay();
}
void draw()
{
    glScalef(3.0, 3.0, 1.0);
    int t;
    if (d == 15)
    {
        glColor3f(1.0, 0.0, 0.0);
        drawString1(GLUT_BITMAP_HELVETICA_18, 75, 100, (char*)"Queue Full");
        //full=1;
    }
    if (d > 15)
    {
        d--;
        full = 1;
        glColor3f(1.0, 0.0, 0.0);
        drawString1(GLUT_BITMAP_HELVETICA_18, 75, 100, (char*)"Queue Full");
    }
    if (!full)
    {
        for (m = 0, del = 0; m < count1; m++)
            del += 4;
        printf("count = % d\n", d);
        for (t = count1; t < d; t++)
        {
            glColor3f(m1[t], m2[t], m3[t]);
            del++;
            glBegin(GL_TRIANGLES);
            glVertex2i(10, (h * del + 10));
            glVertex2i(10 + side, h * del + 10);
            del += 3;
            glVertex2i(10 + (side * 0.5), h * del + 10);
            glEnd();
            glFlush();
        }
    }

}

void delt()
{
    glScalef(3.0, 3.0, 1.0);
    int b;
    if (count1 == d - 1 && d != 0)
    {
        glColor3f(1.0, 0.0, 0.0);
        drawString1(GLUT_BITMAP_HELVETICA_18, 75, 80, (char*)"Queue empty");
    }
    d = d - 1;
    printf("count = %d\n",d);
    d = d + 1;
    glFlush();
    int t, m;
    count1++;
    for (m = 0, del = 0; m < count1; m++)
        del += 4;
    for (t = count1; t < d; t++)
    {
        glColor3f(m1[t], m2[t], m3[t]);
        del++;
        glBegin(GL_TRIANGLES);
        glVertex2i(10, (h * del + 10));
        glVertex2i(10 + side, h * del + 10);
        del += 3;
        glVertex2i(10 + (side * 0.5), h * del + 10);
        glEnd();
        glFlush();
    }
}

// TO DRAW A STRING ON THE DISPLAY
void drawString1(void* font, float x, float y, char* str)
{
    /* Draws string �str� in font �font�, at world (x,y,0) */
    char* ch;
    glRasterPos3f(x, y, 0.0);// TO POINT POINTER TO SPECIFIED POSITION
    for (ch = str; *ch; ch++)//*CH = CH!=0
    {
        glutBitmapCharacter(font, *ch);
    }
}
void display1(void)
{
    if (i == 0)
        glFlush();
    i++;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 0.3, 1.0);
    drawString1(GLUT_BITMAP_HELVETICA_18, 175, 475, (char*)"Implementation of Queue");
    
}
void myinit()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}
void queuewin()
{
    glClearColor(192.0, 192.0, 192.0, 1.0);
    glFlush();
}

