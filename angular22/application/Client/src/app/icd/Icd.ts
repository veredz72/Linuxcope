
export class Icd
{
    /********************************************************************/
    public static GetString (Array32 : number[]) : string 
    {
        let Offset8 = 0;
        let Offset32 = 0;
    
        //Define bytes array. size = uint32 array * 4 (4 bytes in word)
        let Array8 = new Uint8Array (Array32.length * 4);
        //Extract bytes from uin32 array into bytes array
        for (let i=0;i<Array32.length;i++)
        {
        Array8[Offset8++] = Array32[Offset32] & 0xFF;
        Array8[Offset8++] = (Array32[Offset32] & 0xFF00) >> 8;
        Array8[Offset8++] = (Array32[Offset32] & 0xFF0000) >> 16;
        Array8[Offset8++] = (Array32[Offset32] & 0xFF000000) >> 24;
        Offset32++;
        }
        
        let bytesView = new Uint8Array(Array8);
        const decoder = new TextDecoder('utf-8');
        //Return uint8 array without 0 at end of array
        return decoder.decode(bytesView).replace(/\0+$/, '');;
    }
}
