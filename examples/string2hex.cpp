#include "xiso_string.h"

#include <iostream>
using namespace std;

int main()
{
    std::string str =
        "00000001000668afff10023e00000800450005dc792f200040114a27c0a80858c0a80812d83b15b111f47378ffffe1e10200000000000000000b9d470000006400"
        "0000640000000000000000000000660000000000c901100077a2004550a29217df92ba040000007b7701c200d100aa3114ad0c3a8001a27b777b777b777b7700c9"
        "01100092de0045509f2417df91be040000007b9201c200d100aa1f1cdde0450001de7b927b927b927b9200c9011000e9c600455099cc17df9172040000007ce901"
        "c200d100aa3bc471eccb0001c67ce97ce97ce97ce900c901100046cc004550b35c17df8f4f04000000824601c200d100aa6f705e88e36001cc8246824682468246"
        "00c90110009319004550b30717df8ec604000000839301c200d100aa84ec6018657001cc839383938393839300c90710000530004550a5e217df955a0400000084"
        "050032003200aaeb288a4891f00130840584058405840500c90110005319004550c41417dfa20404000000845301c200d100aaf2f83afcb0700150845384538453"
        "845300c90110005419004550d07817dfa45a04000000845401c200d100aa1bfc319cb0d00147845484548454845400c901100075d0004550caf617dfa1aa040000"
        "00847501c200d100aa25c03584bdb001d0847584758475847500c90110007619004550c9bb17dfa29304000000847601c200d100aa0fe0364cbe20012584768476"
        "8476847600c90110007dd20045509c0117df90dd04000000847d01c200d100aaff142d90c0d001d2847d847d847d847d00c90110008cd0004550a3b617df986f04"
        "000000848c01c200d100aa30d48e30c6b001d0848c848c848c848c00c907100096de004550d0b717dfa2760400000084960032003200aa38e4319ccaa001de8496"
        "84968496849600c9011000a319004550c50017dfa3fc0400000084a301c200d100aad8cc39d0cfb001de84a384a384a384a300c9011000ad19004550c07017df9d"
        "5a0400000084ad01c200d100aa2f203facd39001db84ad84ad84ad84ad00c9011000d9ed004550bcf917df9b800400000084d901c200d100aa3ccc445ce4c001ed"
        "84d984d984d984d900c9011000dbd4004550abd817df9ab80400000084db01c200d100aa90ec66bce59001d484db84db84db84db00c9011000ff1a004550bedf17"
        "df9df10400000084ff01c200d100aa17b0413cf3a0010984ff84ff84ff84ff00c90710000910004550a87d17df8e320400000085090032003200aa91d09024f780"
        "0110850985098509850900c90710001417004550c23d17df9c0c0400000085140032003200aa55683e1cfbd00117851485148514851400c90110001a15004550b1"
        "cf17df9eb104000000851a01c200d100aa80845460fe200115851a851a851a851a00c90110003a19004550b52d17df994904000000853a01c200d100aa311451a4"
        "0aa00118853a853a853a853a00c90110003e18004550b03d17df95a804000000853e01c200d100aa6f3060180c400118853e853e853e853e00c90710004e1c0045"
        "50abf117df8f2904000000854e0032003200aa628c79e01280011c854e854e854e854e00c90010005c19004550c0e017df9a4f04000000855c0032003200aa7124"
        "401017f0011a855c855c855c855c00c9011000651f004550af5c17df972004000000856501c200d100aa349860e01b70011f856585658565856500c90110007726"
        "004550ca7617dfa7c804000000857701c200d100aac60c352022800126857785778577857700c90710008319004550b44017dfa26d0400000085830032003200aa"
        "4ee84dbc27300122858385838583858300c90110008627004550db6417dfa96f04000000858601c200d100aa10442bc028600127858685868586858600c9071000"
        "8919004550c3b817dfa39c0400000085890032003200aad5483afc29800123858985898589858900c90710008a74004550c15417dfa66b04000000858a00320032"
        "00aa93a83c8c29e00174858a858a858a858a00c90110008c1a004550aecf17df9ca204000000858c01c200d100aa89805c942ab00124858c858c858c858c00c901"
        "10009173004550d80017dfa92504000000859101c2";

    unsigned char buf[65535] = {0};

    int len = xiso::hexstr2bytes(buf, 1024, str.c_str(), str.length());
    std::cout << xiso::bytes2hexstr(buf, len) << std::endl;

    return 0;
}
