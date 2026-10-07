import {HeaderRequest, SIZEOF_INT32} from './Header'
import {HeaderReply} from './Header'
import {E_PC_TO_TGT_CODE} from './Header'
import {PC_TO_TGT_MAGIC} from './Header'

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
export class RecordControlReply {
    constructor (){
        this.Header = new HeaderReply;
    }
    Header  : HeaderReply;
    
    public DeSerialize (val : object)
    {
        
    }
 }
