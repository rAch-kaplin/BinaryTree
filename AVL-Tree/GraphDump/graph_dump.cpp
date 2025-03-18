// #include <stdio.h>
// #include <stdlib.h>
//
// #include "../AVLTree.h"
//
// TreeErrors TreeDumpDot(AVLTree* Root)
// {
//     static int dump_counter = 0;
//     const size_t PNG_NAME_SIZE = 30;
//     const size_t BUFFER_SIZE = 8192;
//     char* buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
//     if (buffer == nullptr)
//     {
//         fprintf(stderr, "Memory allocation failed\n");
//         return ALLOC_ERR;
//     }
//
//     int buffer_len = 0;
//
//     buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - (size_t)buffer_len,
//                            "digraph G {\n"
//                            "\trankdir = HR;\n"
//                            "\tbgcolor=\"#F7F9FB\"\n");
//
//     buffer_len += GenerateGraph(Root, buffer, &buffer_len, BUFFER_SIZE);
//
//     buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - (size_t)buffer_len, "}\n");
//
//     FILE* dump_file = fopen("GraphDump/dump.dot", "w+");
//     if (!dump_file)
//     {
//         fprintf(stderr, "Failed to open dump.dot\n");
//         free(buffer);
//         return FILE_NOT_OPEN;
//     }
//
//     fprintf(dump_file, "%s", buffer);
//     fclose(dump_file);
//     free(buffer);
//
//     char png_filename[PNG_NAME_SIZE];
//     snprintf(png_filename, PNG_NAME_SIZE, "GraphDump/img/dump_%d.png", dump_counter++);
//
//     char command[256];
//     snprintf(command, sizeof(command), "dot -Tpng GraphDump/dump.dot -o %s", png_filename);
//     system(command);
//
//     return OK;
// }
//
// int GenerateGraph(AVLTree *Node, char* buffer, int* buffer_len, const size_t BUFFER_SIZE)
// {
//     if (!Node) return 0;
//
//
//     *buffer_len += snprintf(buffer + *buffer_len, BUFFER_SIZE - (size_t)*buffer_len,
//                        "\tnode%p [shape=Mrecord; style=filled; color=\"#769074\"; label = <\n"
//                        "\t\t         <table BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" BGCOLOR=\"#769074\" COLOR=\"black\">\n"
//                        "\t\t\t           <tr><td align='center' colspan='2'> Node: %p </td></tr>\n"
//                        "\t\t\t           <tr><td  align='center' colspan='2'> Value: %03d </td></tr>\n"
//                        "\t\t\t           <tr><td  align='center' colspan='2'> Height: %03d </td></tr>\n"
//                        "\t\t\t           <tr><td  PORT='left'  align='center'> Left: %p </td>\n"
//                        "\t\t\t               <td  PORT='right' align='center'> Right: %p </td></tr>\n"
//                        "\t\t         </table> >];\n",
//
//                             Node, Node, Node->value, Node->height, Node->left, Node->right);
//
//     if (Node->left)
//     {
//         *buffer_len += GenerateGraph(Node->left, buffer, buffer_len, BUFFER_SIZE);
//         *buffer_len += snprintf(buffer + *buffer_len, BUFFER_SIZE - (size_t)*buffer_len,
//                                  "\t node%p:left -> node%p [style=bold; weight=1000; ];\n", Node, Node->left);
//     }
//
//     if (Node->right)
//     {
//         *buffer_len += GenerateGraph(Node->right, buffer, buffer_len, BUFFER_SIZE);
//         *buffer_len += snprintf(buffer + *buffer_len, BUFFER_SIZE - (size_t)*buffer_len,
//                                 "\t node%p:right -> node%p [style=bold; weight=1000; ];\n", Node, Node->right);
//     }
//
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../AVLTree.h"

TreeErrors TreeDumpDot(AVLTree* Root)
{
    static int dump_counter = 0;
    const size_t PNG_NAME_SIZE = 30;
    const size_t BUFFER_SIZE = 8192;
    char* buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == nullptr)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return ALLOC_ERR;
    }

    int buffer_len = 0;

    buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - (size_t)buffer_len,
                           "digraph G {\n"
                           "\trankdir = HR;\n"
                           "\tbgcolor=\"#4A5949\"\n");

    buffer_len += GenerateGraph(Root, buffer, &buffer_len, BUFFER_SIZE);

    buffer_len += snprintf(buffer + buffer_len, BUFFER_SIZE - (size_t)buffer_len, "}\n");

    FILE* dump_file = fopen("GraphDump/dump.dot", "w+");
    if (!dump_file)
    {
        fprintf(stderr, "Failed to open dump.dot\n");
        free(buffer);
        return FILE_NOT_OPEN;
    }

    fprintf(dump_file, "%s", buffer);
    fclose(dump_file);
    free(buffer);

    char png_filename[PNG_NAME_SIZE];
    snprintf(png_filename, PNG_NAME_SIZE, "GraphDump/img/dump_%d.png", dump_counter++);

    char command[256];
    snprintf(command, sizeof(command), "dot -Tpng GraphDump/dump.dot -o %s", png_filename);
    system(command);

    return OK;
}

int GenerateGraph(AVLTree *Node, char* buffer, int* buffer_len, const size_t BUFFER_SIZE)
{
    if (!Node) return 0;

    // Создаем узел в Graphviz формате
    *buffer_len += snprintf(buffer + *buffer_len, BUFFER_SIZE - (size_t)*buffer_len,
                       "\tnode%p [shape=Mrecord; style=filled; color=\"#769074\"; label = <\n"
                       "\t\t         <table BORDER=\"1\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"2\" BGCOLOR=\"#769074\" COLOR=\"black\">\n"
                       "\t\t\t           <tr><td align='center' colspan='2'> Node: %p </td></tr>\n"
                       "\t\t\t           <tr><td  align='center' colspan='2'> Value: %03d </td></tr>\n"
                       "\t\t\t           <tr><td  align='center' colspan='2'> Height: %03d </td></tr>\n"
                       "\t\t\t           <tr><td  PORT='left'  align='center'> Left: %p </td>\n"
                       "\t\t\t               <td  PORT='right' align='center'> Right: %p </td></tr>\n"
                       "\t\t         </table> >];\n", Node, Node, Node->value, Node->height, Node->left, Node->right);

    if (Node->left)
    {
        *buffer_len += GenerateGraph(Node->left, buffer, buffer_len, BUFFER_SIZE);
        *buffer_len += snprintf(buffer + *buffer_len, BUFFER_SIZE - (size_t)*buffer_len,
                                 "\t node%p -> node%p [style=bold; weight=1000; ];\n", Node, Node->left);
    }

    if (Node->right)
    {
        *buffer_len += GenerateGraph(Node->right, buffer, buffer_len, BUFFER_SIZE);
        *buffer_len += snprintf(buffer + *buffer_len, BUFFER_SIZE - (size_t)*buffer_len,
                                "\t node%p -> node%p [style=bold; weight=1000; ];\n", Node, Node->right);
    }

    return 0;
}
