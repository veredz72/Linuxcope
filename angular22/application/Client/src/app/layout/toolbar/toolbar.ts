import { Component } from '@angular/core';
import { MatToolbarModule } from '@angular/material/toolbar';
import { MatButtonModule } from '@angular/material/button';
import { MatIconModule } from '@angular/material/icon';

@Component({
  imports: [MatToolbarModule, MatButtonModule, MatIconModule],
  selector: 'app-toolbar',
  styleUrl: './toolbar.css',
  templateUrl: './toolbar.html',
})
export class Toolbar {

  onPlay(): void {
    console.log('Play button clicked');
  }

  onStop(): void {
    console.log('Stop button clicked');
  }
}
