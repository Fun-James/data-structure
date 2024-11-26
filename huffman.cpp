#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

struct weightdata
{
    char ch;
    int weight;
    string code; // 用于存储哈夫曼编码
};

struct HuffmanNode
{
    char ch;
    int weight;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char c, int w) : ch(c), weight(w), left(nullptr), right(nullptr) {}
};
void weightCalculate(string originStr, int *weight)
{
    for (int i = 0; i < originStr.length(); i++)
    {
        if (originStr[i] >= 'a' && originStr[i] <= 'z')
        {
            weight[originStr[i] - 'a']++;
        }
    }
}

weightdata *extractWeights(const string &originStr, int &count)
{
    int weight[26] = {};
    weightCalculate(originStr, weight);

    count = 0;
    for (int i = 0; i < 26; i++)
    {
        if (weight[i] != 0)
        {
            count++;
        }
    }

    weightdata *data = new weightdata[count];
    int count1 = 0;
    for (int i = 0; i < 26; i++)
    {
        if (weight[i] != 0)
        {
            data[count1].ch = 'a' + i;
            data[count1].weight = weight[i];
            count1++;
        }
    }

    return data;
}

HuffmanNode *makeHuffmanTree(weightdata data[], int n)
{
    vector<HuffmanNode *> nodes;
    for (int i = 0; i < n; i++)
    {
        nodes.push_back(new HuffmanNode(data[i].ch, data[i].weight));
    }
    while (nodes.size() > 1)
    {
        // 找到最小的两个节点
        int min = 0, secmin = 1; // min和secmin是最小和第二小的位置
        if (nodes[min]->weight > nodes[secmin]->weight)
        {
            swap(min, secmin);
        }
        for (int i = 2; i < nodes.size(); i++)
        {
            if (nodes[i]->weight < nodes[min]->weight)
            {
                secmin = min;
                min = i;
            }
            else if (nodes[i]->weight < nodes[secmin]->weight && nodes[i]->weight > nodes[min]->weight)
            {
                secmin = i;
            }
        }
        // 合并这两个节点
        HuffmanNode *left = nodes[min];
        HuffmanNode *right = nodes[secmin];
        HuffmanNode *merged = new HuffmanNode('\0', left->weight + right->weight);
        merged->left = left;
        merged->right = right;

        // 删除已合并的节点并插入新节点
        if (min < secmin)
        {
            nodes.erase(nodes.begin() + secmin);
            nodes.erase(nodes.begin() + min);
        }
        else
        {
            nodes.erase(nodes.begin() + min);
            nodes.erase(nodes.begin() + secmin);
        }
        nodes.push_back(merged);
    }
    return nodes[0];
}

void buildHuffmanCode(HuffmanNode *root, string str, weightdata data[], int n)
{
    if (!root)
        return;

    if (root->ch != '\0')
    {
        for (int i = 0; i < n; i++)
        {
            if (data[i].ch == root->ch)
            {
                data[i].code = str;
                break;
            }
        }
    }

    buildHuffmanCode(root->left, str + "0", data, n);
    buildHuffmanCode(root->right, str + "1", data, n);
}

void printHuffmanTree(HuffmanNode *root, string str)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->ch != '\0')
    {
        cout << root->ch << ": " << str << endl;
    }

    printHuffmanTree(root->left, str + "0");
    printHuffmanTree(root->right, str + "1");
}

string encodeString(const string &originStr, weightdata data[], int n)
{
    string encodedStr;
    for (int i = 0; i < originStr.length(); i++)
    {
        if (originStr[i] >= 'a' && originStr[i] <= 'z')
        {
            for (int j = 0; j < n; j++)
            {
                if (data[j].ch == originStr[i])
                {
                    encodedStr += data[j].code;
                    break;
                }
            }
        }
    }
    return encodedStr;
}

string decodeString(const string &encodedStr, HuffmanNode *root)
{
    string decodedStr;
    HuffmanNode *current = root;
    for (int i = 0; i < encodedStr.length(); i++)
    {
        if (encodedStr[i] == '0')
        {
            current = current->left;
        }
        else if (encodedStr[i] == '1')
        {
            current = current->right;
        }

        // 如果到达叶子节点
        if (current->left == nullptr && current->right == nullptr)
        {
            decodedStr += current->ch;
            current = root; // 回到根节点
        }
    }
    return decodedStr;
}

int main()
{
    string originStr;
    getline(cin, originStr);

    int count;
    weightdata *data = extractWeights(originStr, count);

    HuffmanNode *root = makeHuffmanTree(data, count);
    buildHuffmanCode(root, "", data, count);
    printHuffmanTree(root, "");

    string encodedStr = encodeString(originStr, data, count);
    cout << "Encoded String: " << encodedStr << endl;

    string decodedStr = decodeString(encodedStr, root);
    cout << "Decoded String: " << decodedStr << endl;
    delete[] data;
    return 0;
}