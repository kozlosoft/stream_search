import React, { Component } from 'react';
import './App.css';
import $ from 'jquery';

class App extends Component {
  defaultHtml = '<div><i class="src">abc</i>abcdef <i class="src">abc</i> <i class="src">aa</i></div>';
  state = {
    html: this.defaultHtml,
    wordToHighlight: ""
  }

  componentDidMount() {
    const uniqueWords = this.getUniqueWords();
    if (this.state.wordToHighlight === "" && uniqueWords.length > 0) {
      this.handleWordChange({
        target: {
          value: uniqueWords[0]
        }
      });
    }
  }

  render() {
    const uniqueWords = this.getUniqueWords();
    const options = uniqueWords.map(word =>
      <option key={word} value={word}>{word}</option>
    );

    return (
      <div className="App">
        <p>insert html:</p>
        <input
          defaultValue={this.defaultHtml}
          onChange={this.handleHtmlChange}></input>
        <p>select a word to <span className="highlight">highlight</span>: </p>
        <select value={this.state.wordToHighlight} onChange={this.handleWordChange}>
          {options}
        </select>
        <p>rendered html:</p>
        <div dangerouslySetInnerHTML={{ __html: this.state.html }}></div>
      </div>
    );
  }

  handleHtmlChange = (e) => {
    this.setState({
      html: e.target.value
    })
  }

  handleWordChange = (e) => {
    let guestHtml = $(this.state.html);

    let elements = $(`i.src`, guestHtml);
    elements.removeClass("highlight");

    elements = $(`i.src:contains(${e.target.value})`, guestHtml);
    elements.addClass("highlight");
    this.setState({
      wordToHighlight: e.target.value,
      html: guestHtml.prop("outerHTML")
    })
  }

  getUniqueWords = () => {
    const elements = $('i.src', this.state.html);
    return [...new Set(
      elements.get().map(item => { return item.innerText }))];
  }
}

export default App;
