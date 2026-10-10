import {HeaderRequest, SIZEOF_INT32} from './Header'
import {HeaderReply} from './Header'
import {E_PC_TO_TGT_CODE} from './Header'
import {PC_TO_TGT_MAGIC} from './Header'

export const N_MAX_RECORDS=1024;
export const N_MAX_EVENTS=16;

/***************************************************** */
export class RecordControlRequest  {
    constructor (){
        this.Header = new HeaderRequest;
        this.Header.Magic = PC_TO_TGT_MAGIC;
        this.Header.Code = E_PC_TO_TGT_CODE.RECORD_CONTROL_REQUEST_CODE;
        this.Header.Length = HeaderRequest.Sizeof () + SIZEOF_INT32;
    }
    Header : HeaderRequest;
    Control : number = 0;

    public Serialize()
    {
        return '{' + this.Header.Serialize() + ',' + this.Control +'}';
    }
}

/***************************************************** */
export class EVENT_DESC
{
    Name : number [];
    Id : number = 0;
    constructor (){
        this.Name = new Array(2);
    }
}

/***************************************************** */
export class EVENT_RECORD
{
    Id : number = 0;
    Value : number = 0;
    Timetag : number[];
    
     constructor (){
        this.Timetag = new Array (2);
    }
}

/***************************************************** */
export class RecordControlReply {
    
    Header  : HeaderReply;
    NofEvents : number=0;
    NofRecords : number=0;
    Event : EVENT_DESC[];
    Record : EVENT_RECORD[];

    constructor (){
        this.Header = new HeaderReply;
        this.Event = new Array (N_MAX_EVENTS);
        for (let i=0;i<N_MAX_EVENTS;i++)
            this.Event[i]=new EVENT_DESC;

        this.Record = new Array(N_MAX_RECORDS);
        for (let i=0;i<N_MAX_RECORDS;i++)
            this.Record[i]=new EVENT_RECORD;
    }

    public DeSerialize (val : ArrayBuffer)
    {
        let Offset=0;
        var arr32 = new Int32Array (val);
        this.Header.Magic = arr32[Offset++];
        this.Header.Code = arr32[Offset++];
        this.Header.Length = arr32[Offset++];

        this.NofEvents = arr32[Offset++];
        this.NofRecords = arr32[Offset++];
        let i=arr32[Offset++];
        for (let i=0;i<N_MAX_EVENTS;i++)
        {
            this.Event[i].Name[0] = arr32[Offset++];
            this.Event[i].Name[1] = arr32[Offset++];
            this.Event[i].Id = arr32[Offset++];
        }

        for (let i=0;i<N_MAX_RECORDS;i++)
        {
            this.Record[i].Id = arr32[Offset++];
            this.Record[i].Value = arr32[Offset++];
            this.Record[i].Timetag[0] = arr32[Offset++];
            this.Record[i].Timetag[1]=arr32[Offset++]
        }
        console.log (Offset*4);
    }
 }
