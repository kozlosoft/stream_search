import React, { Component } from 'react';
import './App.css';
import $ from 'jquery';

class App extends Component {
  defaultHtml = '<div><i class="src">abc</i>abcdef <i class="src">abc</i> <i class="src">aa</i></div>';
  state = {
    html: this.defaultHtml,
    wordToHighlight: "not selected"
  }

  render() {
    const elements = $('i.src', this.state.html);
    const uniqueWords = [...new Set(
      elements.get().map(item => { return item.innerText}))];
    const options = uniqueWords.map(word => 
      <option key={word} value={word}>{word}</option> 
    );

    return (
      <div className="App">
        <p>insert html:</p>
        <input 
          defaultValue={this.defaultHtml}
          onChange={this.handleHtmlChange}></input>
        <p>select a word to highlight: </p>
        <select value={this.state.wordToHighlight} onChange={this.handleWordChange}>
            {options}
          </select>
        <p>rendered html:</p>
        <div dangerouslySetInnerHTML={{__html: this.state.html}}></div>
      </div>
    );
  }

  handleHtmlChange = (e) => {
    this.setState({
      html: e.target.value
    })
  }

  handleWordChange = (e) => {
    this.setState({
      wordToHighlight: e.target.value
    })
  }
}

export default App;
