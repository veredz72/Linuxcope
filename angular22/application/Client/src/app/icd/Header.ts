export enum E_PC_TO_TGT_CODE {
    RECORD_CONTROL_REQUEST_CODE			= 1,
}

export const PC_TO_TGT_MAGIC = 0xCAFE2DAD;
const host = typeof window !== 'undefined' ? window.location.hostname : 'localhost';
export const TGT_IP = `http://${host}:8000`;

export const SIZEOF_INT32 = 4;

export class HeaderRequest  {
    Magic : number =PC_TO_TGT_MAGIC;
    Code : E_PC_TO_TGT_CODE = E_PC_TO_TGT_CODE.RECORD_CONTROL_REQUEST_CODE;
    Length : number = 0;

    public static Sizeof () : number
    {
        return SIZEOF_INT32 * 3;
    }

    public Serialize () : any
    {
        return this.Magic + ',' + this.Code + ',' + this.Length;
    }
}

export class HeaderReply {
    Magic : number =0;
    Code : number =0;
    Length : number =0;

    public static Sizeof () : number
    {
        return SIZEOF_INT32 * 3;
    }
}
