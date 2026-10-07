import { Component } from '@angular/core';
import { MatToolbarModule } from '@angular/material/toolbar';
import { MatButtonModule } from '@angular/material/button';
import { MatIconModule } from '@angular/material/icon';
import {HttpClient} from '@angular/common/http';
import {RecordControlRequest} from '../../icd/RecordControl'
import { TGT_IP } from '../../icd/Header';

@Component({
  imports: [MatToolbarModule, MatButtonModule, MatIconModule],
  selector: 'app-toolbar',
  styleUrl: './toolbar.css',
  templateUrl: './toolbar.html',
})
export class Toolbar {
  isRecording : boolean = false;
  recordControlRequest : RecordControlRequest;

  constructor (private http: HttpClient)
  {
    this.recordControlRequest = new RecordControlRequest;
  }

  onRecord(): void {
    console.log('Record button clicked');
    this.isRecording = !this.isRecording;
    this.recordControlRequest.Control = this.isRecording==true ? 1:0;

    var body = this.recordControlRequest.Serialize();
    console.log (body);
    this.http.post (TGT_IP,body,{responseType: 'arraybuffer'}).subscribe(
      (val) => {
          console.log("POST call successful value returned in body",  val);
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
