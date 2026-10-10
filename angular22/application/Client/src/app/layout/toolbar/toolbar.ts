import { Component } from '@angular/core';
import { MatToolbarModule } from '@angular/material/toolbar';
import { MatButtonModule } from '@angular/material/button';
import { MatIconModule } from '@angular/material/icon';
import {HttpClient} from '@angular/common/http';
import {RecordControlRequest, RecordControlReply} from '../../icd/RecordControl'
import { TGT_IP } from '../../icd/Header';
import { Sharedobject } from '../../../services/sharedobject';
import { Dashboard } from '../dashboard/dashboard';

@Component({
  imports: [MatToolbarModule, MatButtonModule, MatIconModule],
  selector: 'app-toolbar',
  styleUrl: './toolbar.css',
  templateUrl: './toolbar.html',
})
export class Toolbar {
  isRecording : boolean = false;
  recordControlRequest : RecordControlRequest;
  recordControlReply : RecordControlReply

  /******************************************************************************/
  constructor (private http: HttpClient, private sharedObject: Sharedobject)
  {
    this.recordControlRequest = new RecordControlRequest;
    this.recordControlReply = new RecordControlReply;
  }

  /******************************************************************************/
  onRecord(): void {
    console.log('Record button clicked');
    this.isRecording = !this.isRecording;
    this.recordControlRequest.Control = this.isRecording==true ? 1:0;

    var body = this.recordControlRequest.Serialize();
    console.log (body);
    this.http.post (TGT_IP,body,{responseType: 'arraybuffer'}).subscribe(
      (val) => {
          console.log("POST call successful value returned in body",  val);
          let Dashboard:Dashboard = this.sharedObject.DashboardObject;
          if (this.recordControlRequest.Control==0)
          {
            this.recordControlReply.DeSerialize (val);
            Dashboard.UpdateView (this.recordControlReply);
          }
      },
      response => {
          console.log("POST call in error", response);
      },
      () => {
          //console.log("The POST observable is now completed.");
      });
  }

  onOpen(): void {
    console.log('Open button clicked');
  }
}
