import { Component } from '@angular/core';
import { MatToolbarModule } from '@angular/material/toolbar';
import { MatButtonModule } from '@angular/material/button';
import { MatIconModule } from '@angular/material/icon';
import {HttpClient} from '@angular/common/http';
import {RecordControlRequest} from '../../icd/RecordControl'

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
  }

  onOpen(): void {
    console.log('Open button clicked');
  }
}
